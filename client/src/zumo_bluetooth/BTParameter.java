package zumo_bluetooth;

public class BTParameter {

	private String type;
	private String name;
	private String value;
	private String originalString;
	
	public BTParameter(String request) {
		type = request.substring(1, 4);
		name = request.substring(4,request.indexOf(":"));
		value = request.substring(request.indexOf(":") + 1, request.length()-2);
		originalString = request;
	}
	
	
	public String getType() {
		return type;
	}
	
	public String getName() {
		return name;
	}
	
	public String getValue() {
		return value;
	}
	
	public void setValue(String value) {
		this.value = value;
	}
	
	public String getOriginalString() {
		return originalString;
	}
	
}
