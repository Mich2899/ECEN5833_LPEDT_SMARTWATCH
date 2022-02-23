/*
 * scheduler.c
 *
 *  Created on: Sep 14, 2021
 *      Author: Dhruv
 *      Brief : Contains the scheduler to handle events such as scheduling a temperature
 *              sensor acquisition from the Si7021 sensor every 3 seconds.
 */

#include "scheduler.h"

enum States{CONFIG, WAIT_SD, START_CONV, WAIT_OS_I2C, MEASURE, REPORT};
enum Events{evtNone, evtLETIMER0_UF, evtLETIMER0_COMP1, evtI2C0_Complete};

enum Events currentevt = evtNone;
enum States currentste = CONFIG;

uint32_t getNextEvent()
{
  uint32_t evt;

  /* Get the current event status */
  evt = currentevt;

  /* Clear the current event */
  CORE_CRITICAL_SECTION(currentevt = evtNone;);

  return evt;
}

void app_process_action()
{
  uint32_t evt;
  I2C_TransferReturn_TypeDef I2CTransferReturnStatus;

  /* Get the next event */
  evt = getNextEvent();

  /* Event handling */
  switch(currentste)
  {
    /* CONFIG State, Set the Conversion Mode to Shutdown Mode (SD) */
    case CONFIG:
          currentste = WAIT_SD;
          sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
          setShutdownModeTMP117();
      /* Go to sleep */
      break;

    /* WAIT State, Wait till I2C Transfer is complete and go back to low-power */
    case WAIT_SD:
      if(evt == evtI2C0_Complete)
        {
          /* Disable IRQ on successful transfer */
          I2CTransferReturnStatus = getI2CTransferReturn();
          if(I2CTransferReturnStatus == i2cTransferDone)
            NVIC_DisableIRQ(I2C0_IRQn);

          currentste = START_CONV;
          sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
        }
      break;

    /* START Conversion State, check if UF event has occurred, Set the Conversion
     * Mode to One-Shot Mode (OS) */
    case START_CONV:
      if(evt == evtLETIMER0_UF)
        {
          currentste = WAIT_OS_I2C;
          sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
          setOneShotModeTMP117();
        }
      break;

      /* WAIT State, Wait till I2C Transfer is complete and start timer for conversion */
      case WAIT_OS_I2C:
        if(evt == evtI2C0_Complete)
          {
            /* Disable IRQ on successful transfer */
            I2CTransferReturnStatus = getI2CTransferReturn();
            if(I2CTransferReturnStatus == i2cTransferDone)
              NVIC_DisableIRQ(I2C0_IRQn);

            currentste = MEASURE;
            sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
            timerWaitUs_irq(125*1000);
          }
        break;

      /* WAIT State, Wait till conversion complete and go back to low-power */
      case MEASURE:
        if(evt == evtLETIMER0_COMP1)
          {
            currentste = REPORT;
            sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
            getTemperatureTMP117();
          }
        break;

      /* REPORT State, Wait till I2C Transfer is complete and log the temperature */
      case REPORT:
        if(evt == evtI2C0_Complete)
          {
            I2CTransferReturnStatus = getI2CTransferReturn();
            if(I2CTransferReturnStatus == i2cTransferDone)
              NVIC_DisableIRQ(I2C0_IRQn);

            sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);

            currentste = START_CONV;
            reportTemperatureTMP117();
          }
        break;

  }

}

void schedulerSetEvent_UF()
{
  CORE_CRITICAL_SECTION(currentevt = evtLETIMER0_UF;);
}

void schedulerSetEvent_COMP1()
{
  CORE_CRITICAL_SECTION(currentevt = evtLETIMER0_COMP1;);
}

void schedulerSetEvent_I2Cdone()
{
  CORE_CRITICAL_SECTION(currentevt = evtI2C0_Complete;);
}
