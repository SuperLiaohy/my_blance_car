
#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"
#include "gpio.h"
#include "i2c.h"
#include "MPU6050.h"
#include "tim.h"

#ifdef __cplusplus
}
#endif

#include "motor.h"
#include "pid.h"
#include "oled.h"
extern int time;
extern "C" void  SystemClock_Config(void);
float pitch, roll, yaw;
int main(void)
{


    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM5_Init();
    MX_TIM6_Init();

    OLED_Init();
    OLED_ShowString(1,1,"waiting...");
    uint8_t res;
    res = MPU6050_DMP_Init();
    if(res != 0)
    {
        OLED_ShowString(1,1,"Init Err!  ");
        while (res){
            HAL_Delay(1000);
            res = MPU6050_DMP_Init();
        }
        OLED_ShowString(1,1,"Init OK!   ");
    }
    else
    {
        OLED_ShowString(1,1,"Init OK!   ");
    }
    HAL_Delay(1000);
    OLED_Clear();


    HAL_TIM_Base_Start_IT(&htim6);
    FrontLeft.Init();
    FrontRight.Init();

    while (1)
    {

        MPU6050_DMP_Get_Data(&pitch, &roll, &yaw);
//        OLED_ShowNum(1,13,time,2);
//        OLED_ShowString(1,1,"roll:");
//        OLED_Showfloat(1, 6, roll, 3,2);
//        OLED_ShowString(2,1,"pitch:");
//        OLED_Showfloat(2, 7, pitch, 3,2);
//        OLED_ShowString(3,1,"yaw:");
//        OLED_Showfloat(3, 5, yaw, 3,2);
//        FrontLeft.SetPwm(1000);//600 25
//        FrontRight.SetPwm(1000);//1000 42
//        OLED_ShowSignedNum(4,1,FrontLeft.speed,5);
//        OLED_ShowSignedNum(4,8,FrontRight.speed,5);
    }

}




























void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
