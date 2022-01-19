/***************************************************/
/* Author  : fatma                                 */
/* Date    : 25 Sep 2021                         */
/* version : V04                                   */
/***************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "STK_interface.h"

#include "LEDMRX_interface.h"
#include "LEDMRX_private.h"
#include "LEDMRX_config.h"

#include "Delay.h"

volatile u8 Stop_Animating 	= 0;
volatile u8 Speed			= 40;
volatile u8 Push			= 0;



 void HLEDMRX_voidInit(void)
 {
		for(int iteration =0; iteration<8; iteration++)
		{
			/* Set Row direction */
			MGPIO_voidSetPinDirection(LEDMRX_ROW_PIN[iteration][0],LEDMRX_ROW_PIN[iteration][1], OUTPUT_SPEED_2MHZ_PP);
		     /* Set Column direction */
			MGPIO_voidSetPinDirection(LEDMRX_COL_PIN[iteration][0],LEDMRX_COL_PIN[iteration][1], OUTPUT_SPEED_2MHZ_PP);
		}
 }
	 

static void DisableAllCols(void)
{
	/* Disable all columns */
	for(u8 iteration=0; iteration<8; iteration++)
	{
		MGPIO_voidSetPinValue(LEDMRX_COL_PIN[iteration][0],LEDMRX_COL_PIN[iteration][1], HIGH);
	}
}


static void SetRowValue(u8 Copy_u8Value)
{
	u8 Local_u8BIT;

	for(int iteration=0; iteration<8; iteration++)
	{
		/* Get bit value in desire Row */
		Local_u8BIT = GET_BIT(Copy_u8Value,iteration);

		/*Set value in desire LEDMRX row */
		MGPIO_voidSetPinValue(LEDMRX_ROW_PIN[iteration][0],LEDMRX_ROW_PIN[iteration][1], Local_u8BIT);
	}

}



void HLEDMRX_voidStartAnimating(u8 *Copy_u8Data)
{
		 /* 40 for the size of data array */
	 	for(u8 i=0; i<40 ;i=i+Push)
			{
				while(Stop_Animating);

				for(u8 j = 0; j < Speed; j++)
				{
					 /*  show the 8 column together*/
					for(u8 iteration =0; iteration < 8; iteration++){

					    /* Disable all columns */
						DisableAllCols();

						 /* (j+iteration) to show the next 8 column together in the array, starting from j*/
						SetRowValue(Copy_u8Data[iteration+i]);

						/* Enable the desire column */
						MGPIO_voidSetPinValue(LEDMRX_COL_PIN [iteration][0], LEDMRX_COL_PIN[iteration][1], LOW);

						delay_ms(2);
					}
				}
	}
	 	Push=0;
}


void HLEDMRX_voidPauseAnimating(void)
{
	Stop_Animating = 1;
}

void HLEDMRX_voidResumeAnimating(void)
{
	Stop_Animating = 0;
}

void HLEDMRX_voidPushUp(void)
{
	Push += 8;
}
