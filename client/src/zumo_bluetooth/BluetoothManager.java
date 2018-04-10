package zumo_bluetooth;

import javafx.scene.text.Text;

public class BluetoothManager {

	private PLabSerial btSerial;
	private String name;
	private Text tf;
	
	
	public BluetoothManager(Text textField) {
		this.tf = textField;
		
		
		btSerial = new PLabSerial();
		
		if(btSerial.openPLabPort()) {
			name = btSerial.getOpenPortName();
		} else {
			name = "No Open Port";
		}
		
		tf.setText(name);
		
		btSerial.addListener(this, "receive");
		
	}
	
	public void receive() {
		
	}
	
	public void send(String msg) {
		btSerial.sendMessage(msg);
	}
	
	
}
