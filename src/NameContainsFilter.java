import java.io.File;
import java.io.FilenameFilter;


public class NameContainsFilter implements FilenameFilter {

	String mustContainString;
	
	public NameContainsFilter(String mustContainString) {
		this.mustContainString = mustContainString.toLowerCase();
	}
	
	@Override
	public boolean accept(File dir, String name) {
		if (name.toLowerCase().contains(mustContainString))
			return true;
		else
			return false;
	}

}
