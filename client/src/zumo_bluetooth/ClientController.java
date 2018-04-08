package zumo_bluetooth;

import javafx.fxml.FXML;
import javafx.scene.layout.VBox;

public class ClientController {

	public WindowManager winMng;
	public BluetoothManager btMng;
	
	
	@FXML
	public VBox varContainer;
	
	
	public ClientController() {
		winMng.addParameter(new BTParameter("GINTa:17"));
	}
	
	
	
}
