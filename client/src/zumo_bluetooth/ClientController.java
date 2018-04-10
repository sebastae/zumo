package zumo_bluetooth;

import java.util.ArrayList;

import javafx.fxml.FXML;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class ClientController {

	public WindowManager winMng;
	public BluetoothManager btMng;
	
	public ArrayList<BTParameter> params;
	
	
	@FXML
	public VBox varContainer;
	
	@FXML
	public Text portNameField;
	
	
	public ClientController() {
		params = new ArrayList<>();
	}
	
	@FXML
	public void initialize() {
		winMng = new WindowManager(varContainer, this);
		btMng = new BluetoothManager(portNameField);
	}
	
	
	@FXML
	public void getAll() {
		btMng.send("A;");
	}
	
	public void get(String name) {
		for(BTParameter p : params) {
			if(p.getName().equals(name)) {
				btMng.send("G" + p.getType() + name + ":0;");
			}
		}
	}
	
	public void set(String name, String value) {
		for(BTParameter p : params) {
			if(p.getName().equals(name)) {
				btMng.send("S" + p.getType() + name + ":" + value + ";");
			}
		}
	}
	
	public void addParameter(BTParameter param) {
		for(BTParameter p : params) {
			if(p.getName().equals(param.getName())){
				p.setValue(param.getValue());
				break;
			}
		}
		params.add(param);
		update();
	}
	
	public void update() {
		varContainer.getChildren().clear();
		for(BTParameter p : params) {
			winMng.addParameter(p);
		}
	}
	
	
}
