// коэффицент погрешности, настраиваемый
float k = 0.1;

// функция вычисляет значение на выходе по определенному коэфиценту.
// тип данных на выходе должен быть float, для более мягкого графика
float expRunningAverage(float newVal){
  static float filVal = 0;
  filVal+=(newVal-filVal)*k;
  return filVal;
}
