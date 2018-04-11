package zumo_bluetooth;

import java.util.ArrayList;
import java.util.Stack;

import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class ClientController{

	public WindowManager winMng;
	public BluetoothManager btMng;
	
	private ArrayList<ParameterConnection> connections = new ArrayList<>();
	public Stack<BTParameter> parameters = new Stack<>();
	
	
	
	
	@FXML
	public VBox varContainer;
	

	@FXML
	public TextField portSelector;
	
	@FXML
	public Text status;
	
	
	public ClientController() {
		//connections = new ArrayList<>();
	}
	
	@FXML
	public void initialize() {
		winMng = new WindowManager(varContainer, this);
		btMng = new BluetoothManager(this);
			
	}
	
	@FXML
	public void connect() {
		if(btMng.selectPort(portSelector.getText())) {
			status.setText("Connected");
		} else {
			status.setText("Not connected");
		}
	}
	
	@FXML
	public void close() {
		btMng.close();
		
		if(btMng.isOpen()) {
			status.setText("Connected");
		} else {
			status.setText("Not connected");
		}
		
	}
	
	
	@FXML
	public void getAll() {
		System.out.println("Sending GETALL");
		btMng.send("A;");
	}
	
	public void get(String name) {
		
	}
	
	public void update() {
		while(!parameters.isEmpty()) {
			addParameter(parameters.pop());
		}
	}
	
	public void set(String name, String value) {
		for(ParameterConnection c : connections) {
			if(c.parameter.getName().equals(name)) {
				btMng.send("S" + c.parameter.getType() + name + ":" + value + ";");
			}
		}
	}
	
	public void addParameter(BTParameter param) {
		System.out.println("Called addParameter");
		
		for(ParameterConnection c : connections) {
			System.out.println("Iterating");
			if(c.parameter.getName().equals(param.getName())) {
				c.parameter.setValue(param.getValue());
				c.textField.setText(c.parameter.getValue());
				System.out.println("Updated " + param.getName() + " to " + param.getValue());
				return;
			}
		}
		System.out.println("Adding connection");
		ParameterConnection pc = winMng.addParameter(param);
		System.out.println(connections.toString());
		connections.add(pc);
		System.out.println("Added " + param.getName());
	}
	
}
