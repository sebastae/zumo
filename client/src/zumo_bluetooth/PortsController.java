package zumo_bluetooth;


import com.fazecast.jSerialComm.SerialPort;

import javafx.fxml.FXML;
import javafx.scene.text.Text;

public class PortsController {
	
	@FXML
	public Text ports;
	
	public String portString = "";
	
	
	
	
	@FXML
	public void getPorts() {
		
		portString = "";
		
		//String[] p = serial.getPortNames();
		SerialPort[] p = SerialPort.getCommPorts();
		
		for(SerialPort s : p) {
			portString += (s.getDescriptivePortName() +  " : " + s.getPortDescription()  + "\n");
			
		}
		ports.setText(portString);
	}
	
	

}
