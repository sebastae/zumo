package zumo_bluetooth;

public class BTParameter {

	private String type;
	private String name;
	private String value;
	private String originalString;
	
	public BTParameter(String request) {
		type = (String) request.substring(1, 4);
		name = (String) request.substring(4,request.indexOf(":"));
		value = (String) request.substring(request.indexOf(":") + 1, request.length()-1);
		originalString =  (String)request;
		
		System.out.println("Constructed new BTParameter");
		
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
