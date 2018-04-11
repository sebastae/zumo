package zumo_bluetooth;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.scene.shape.StrokeType;
import javafx.scene.text.Font;
import javafx.scene.text.Text;

public class WindowManager {

	
	private VBox vbx;
	private ClientController ctrl;
	
	public WindowManager(VBox vbx, ClientController ctrl) {
		this.vbx = vbx;
		this.ctrl = ctrl;
	}
	
	public ParameterConnection addParameter(BTParameter param) {
		
		System.out.println("Starting Text");
		
		
		Text txt = new Text();
		
		txt.setLayoutY(28);
		txt.setStrokeType(StrokeType.OUTSIDE);
		txt.setStrokeWidth(0);
		
		txt.setText(param.getName());
		txt.setWrappingWidth(122);
		
		
		Font monospaceFont = new Font("Monospaced Regular", 12);
		
		txt.setFont(monospaceFont);
		
		System.out.println("Starting TextField");
		
		TextField tf = new TextField();
		
		tf.setLayoutY(11);
		tf.setLayoutX(128);
		tf.setPrefHeight(25);
		tf.setPrefWidth(72);
		
		tf.setText(param.getValue());
		
		System.out.println("Staring button");
		
		Button btn = new Button();
		
		btn.setLayoutX(217);
		btn.setLayoutY(11);
		btn.setMnemonicParsing(false);
		btn.setText("Send");
		btn.setOnAction(new EventHandler<ActionEvent>() {
			
			@Override
			public void handle(ActionEvent event) {
				ctrl.set(param.getName(), tf.getText());
				
			}
		});
		
		System.out.println("Starting AnchorPane");
		
		
		AnchorPane ap = new AnchorPane();
		
		
		ap.setPrefWidth(260);
		ap.setPrefHeight(46);
		
		System.out.println("Adding nodes to AnchorPane");
		
		ap.getChildren().add(txt);
		ap.getChildren().add(tf);
		ap.getChildren().add(btn);
		
		System.out.println("Done with node setup");
		System.out.println(ap.toString());
		System.out.println(vbx.toString());
		System.out.println(vbx.getChildren().toString());
		System.out.println(ap.getChildren().toString());
		
		this.vbx.getChildren().add(ap);
		
		System.out.println("Built new Node");
		
		return new ParameterConnection(txt, tf, btn, param);
		
		
	}
}
