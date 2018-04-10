package zumo_bluetooth;


import javafx.fxml.FXML;
import javafx.scene.text.Text;

public class PortsController {
	
	@FXML
	public Text ports;
	
	public String portString = "";
	
	private PLabSerial serial = new PLabSerial();
	
	
	
	
	@FXML
	public void getPorts() {
		
		portString = "";
		
		String[] p = serial.getPortNames();
		
		for(String s : p) {
			portString += (s + "\n");
		}
		ports.setText(portString);
	}
	
	

}
