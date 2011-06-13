import java.io.File;

import junit.framework.TestCase;


public class NameContainsFilterTest extends TestCase {
	NameContainsFilter filter, filter2;

	protected void setUp() throws Exception {
		super.setUp();
		filter = new NameContainsFilter("ThisIsATest");
	}

	protected void tearDown() throws Exception {
		super.tearDown();
	}

	public void testExactMatch() {
		assertTrue(filter.accept(null, "ThisIsATest"));
	}
	
	public void testSameLowerCase() {
		assertTrue(filter.accept(null, "thisisatest"));
	}
	
	public void testSameUpperCase() {
		assertTrue(filter.accept(null, "THISISATEST"));
	}
	
	public void testExactMatchWithOther() {
		assertTrue(filter.accept(null, "AndReallyThisIsATestInABigWorld"));
	}
	
	public void testSameLowerCaseWithOther() {
		assertTrue(filter.accept(null, "andreallythisisatestinabigworld"));
	}
	
	public void testSameUpperCaseWithOther() {
		assertTrue(filter.accept(null, "ANDREALLYTHISISATESTINABIGWORLD"));
	}
	
	public void testDifferent() {
		assertFalse(filter.accept(null, "thisisnotatest"));
	}
}
