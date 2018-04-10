package zumo_bluetooth;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Ports extends Application{

	@Override
	public void start(Stage primaryStage) throws Exception {
		FXMLLoader loader = new FXMLLoader();
		Parent root = (Parent) loader.load(this.getClass().getResourceAsStream("Ports.fxml"));
		primaryStage.setScene(new Scene(root));
		primaryStage.show();
		
	}
	
	public static void main(String[] args) {
		launch(args);
	}

}
