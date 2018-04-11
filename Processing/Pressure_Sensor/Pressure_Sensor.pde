import processing.serial.*;
import controlP5.*;

public static final float chartMaxPressVoltsRange = 5.0;
public static final float chartMinPressVoltsRange = 0.0;
public static final float chartMaxPressValRange = 1200.0;
public static final float chartMinPressValRange = -10.0;

ControlP5 cp5;
Serial myPort;
int lf = 10;
String inVals;
int pressInt = 0;
float pressVoltage, pressVal;

Chart pressVoltsChart;
Chart pressValChart;


void setup() {
  size(900, 400);
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[32], 57600);
  myPort.bufferUntil(lf);
  
  cp5 = new ControlP5(this);
  pressVoltsChart = cp5.addChart("Pressure Sensor Voltage (V)")
               .setPosition(100, 50)
               .setSize(300, 300)
               .setRange(chartMinPressVoltsRange, chartMaxPressVoltsRange)
               .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
               .setStrokeWeight(1.5)
               .setColorCaptionLabel(color(40))
               ;
               
  pressValChart = cp5.addChart("Pressure Sensor (kPa)")
             .setPosition(500, 50)
             .setSize(300, 300)
             .setRange(chartMinPressValRange, chartMaxPressValRange)
             .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
             .setStrokeWeight(1.5)
             .setColorCaptionLabel(color(40))
             ;

  pressVoltsChart.addDataSet("pressVolts");
  pressVoltsChart.setData("pressVolts", new float[100]);
  pressValChart.addDataSet("pressVals");
  pressValChart.setData("pressVals", new float[100]);
  

}


void draw() 
{  
  background(200);
  drawAxes();
  
  
  pressVoltsChart.unshift("pressVolts", pressVoltage);
  pressValChart.unshift("pressVals", pressVal);
}

void serialEvent(Serial ser)
{
  inVals = ser.readString().trim();
  String[] list = split(inVals, ',');
  pressVoltage = float(list[0]);
  pressVal = float(list[1]);
  print(pressVoltage);
  println(", " + pressVal);
}

void drawAxes()
{
  color(0,0,0);
  line(90,50,90,350);
  line(490, 50, 490, 350);
 
  fill(0,0,0);
  for (int i=10; i>=0; i--)
  {
      if (i != 0)
      {
        text(1200-(120*(i-1)), 450, 30*(i-1)+55);
        text(5.0-(0.5*(i-1)), 30, 30*(i-1)+55);
      }
      
      line(80, 30*i+50, 100, 30*i+50);
      line(480, 30*i+50, 500, 30*i+50);
  }
  
}