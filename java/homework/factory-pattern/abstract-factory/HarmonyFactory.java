public class HarmonyFactory implements SystemFactory {
	@Override
	public OperationController createOperationController() {
		return new HarmonyOperationController();
	}

	@Override
	public UiController createUiController() {
		return new HarmonyUiController();
	}
}
