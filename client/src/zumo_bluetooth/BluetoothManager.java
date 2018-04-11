package zumo_bluetooth;


public class BluetoothManager {

	private BluetoothSerial btSerial;
	private ClientController controller;
	
	
	public BluetoothManager(ClientController ctrl) {
		this.controller = ctrl;
		btSerial = new BluetoothSerial();
		
		btSerial.setMessageListener(this, "receive");
		
	}
	
	public void close() {
		btSerial.closePort();
	}
	
	public boolean isOpen() {
		return btSerial.isOpen();
	}
	
	public String[] getPorts() {
		return btSerial.getOpenPorts();
	}
	
	public boolean selectPort(String port) {
		return btSerial.openPort(port);
	}
	
	public void receive(String msg) {
		System.out.println("Received message");
		BTParameter p = new BTParameter(msg);
		controller.addParameter(p);
	}
	
	public void send(String msg) {
		btSerial.send(msg);
		System.out.println(msg);
	}
	
	
}
