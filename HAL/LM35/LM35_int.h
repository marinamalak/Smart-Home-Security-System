/*
 * LM35_int.h
 *
 *  Created on: Nov 6, 2023
 *      Author: aya
 */

#ifndef HAL_LM35_LM35_INT_H_
#define HAL_LM35_LM35_INT_H_

ES_t LM35_enuInit(TR_t *Copy_pstrLM);

ES_t LM35_enuGetTemp(f32 * Copy_pf32Temp);

#endif /* HAL_LM35_LM35_INT_H_ */
