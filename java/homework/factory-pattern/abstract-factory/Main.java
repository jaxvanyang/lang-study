public class Main {
	public static void main(String[] args) {
		SystemFactory systemFactory;
		UiController uiController;
		OperationController operationController;

		// Android
		systemFactory = new AndroidFactory();

		// IOS
		// systemFactory = new IosFactory();

		// Harmony
		// systemFactory = new HarmonyFactory();
		

		uiController = systemFactory.createUiController();
		operationController = systemFactory.createOperationController();

		uiController.display();
		operationController.control();
	}
}
