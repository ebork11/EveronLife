modded class SCR_PlayerController
{	
	override void UpdateLocalPlayerController()
	{
		super.UpdateLocalPlayerController();
		
		if (!m_bIsLocalPlayerController)
			return;
		
		InputManager inputManager = GetGame().GetInputManager();
		
		inputManager.AddActionListener("EL_OpenPhone", EActionTrigger.DOWN, Action_OpenPhone );
	}
	
	void Action_OpenPhone() 
	{
		Print("Hello world");
	}
}