package zumo_bluetooth;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;

public class ParameterConnection {

	@FXML
	public Text text;
	
	@FXML
	public TextField textField;
	
	@FXML
	public Button button;
	
	BTParameter parameter;
	
	public ParameterConnection(Text t, TextField tf, Button b, BTParameter p) {
		text = t;
		textField = tf;
		button = b;
		parameter = p;
	}
}
