package zumo_bluetooth;

import java.io.OutputStream;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;

import javafx.application.Platform;

public class BluetoothSerial {

	private SerialPort activePort = null;
	private String charBuffer = "";
	private String endChar = ";";
	
	private Object callbackObject;
	private String callbackMethod;
	
	
	
	
	
	public String[] getOpenPorts() {
		SerialPort[] ports = SerialPort.getCommPorts();
		ArrayList<String> portCodes = new ArrayList<>();
		for(SerialPort p : ports) {
			portCodes.add(p.getSystemPortName());
		}
		return portCodes.toArray(new String[portCodes.size()]);
	}
	
	public boolean isOpen() {
		if(activePort != null) return activePort.isOpen();
		else return false;
	}
	
	public boolean openPort(String name) {
		if(Arrays.asList(getOpenPorts()).indexOf(name) > -1) {
			
			activePort = SerialPort.getCommPort(name);
			
			if(activePort.isOpen()) {
				activePort.closePort();
			}
			
			if(activePort.openPort()) {
				activePort.addDataListener(new SerialPortDataListener() {
					
					@Override
					public void serialEvent(SerialPortEvent event) {
						if(event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) {
							return;
						}
						
						byte[] incomingData = new byte[activePort.bytesAvailable()];
						int numRead = activePort.readBytes(incomingData, incomingData.length);
						
						charBuffer += new String(incomingData, 0, numRead);
						
						commitBuffer();
						
					}
					
					@Override
					public int getListeningEvents() {
						return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
					}
				});
				return true;
			}
			System.out.println(name + " : Could not open port");
			System.out.println(name + " is" + (activePort.isOpen()?" not ":" ") + "open");
			return false;
		}
		System.out.println(name + " : No such port");
		return false;
	}
	
	public void closePort() {
		if(activePort != null) {
			activePort.closePort();
			activePort = null;
		}
	}
	
	public void setMessageListener(Object obj, String callbackMethod) {
		this.callbackObject = obj;
		this.callbackMethod = callbackMethod;
	}
	
	public void setEndChar(String s) {
		endChar = s;
	}
	
	public void send(String msg) {
		if(activePort != null) {
			byte[] buffer = new byte[msg.length()];
			for(int i = 0; i < msg.length(); i++) {
				buffer[i] = (byte) msg.charAt(i);
			}
			
			OutputStream output = activePort.getOutputStream();
			
			try {
				output.write(buffer, 0, buffer.length);
			} catch (Exception e) {
				System.out.println("Could not send message: " + msg);
			}
		}
	}
	
	public void callback(String msg) {
		if(callbackMethod != null && callbackObject != null) {
			Method method = null;
			try {
				method = callbackObject.getClass().getMethod(callbackMethod, String.class);
			} catch (Exception e) {
				// TODO: handle exception
			}
			
			if(method != null) {
				try {
				Object[] args = {msg};
				method.invoke(callbackObject, args);
				} catch (Exception e) {
					// TODO: handle exception
				}
			}
		}
	}
	
	public void commitBuffer() {
		String msg = "";
		while(charBuffer.indexOf(endChar) > -1) {
			int endPos = charBuffer.indexOf(endChar);
			if(endPos != 0) {
				msg = charBuffer.substring(0, endPos+1);
				charBuffer = charBuffer.substring(endPos+1);
			}
			final String message = msg;
			boolean runLater = Platform.isFxApplicationThread();
			if(runLater) {
				Platform.runLater(new Runnable() {
					
					@Override
					public void run() {
						try {
							callback(message);
						} catch (Exception e) {
							// TODO: handle exception
						}
						
					}
				});
			} else {
			
			
			callback(msg);
			}
			
			
		}
	}

}
