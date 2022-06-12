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
		IEntity user = IEntity.Cast(GetGame().GetPlayerController().GetControlledEntity());
		if (!user)
			return;
			
		SCR_CharacterControllerComponent characterControllerComponent = SCR_CharacterControllerComponent.Cast(user.FindComponent(SCR_CharacterControllerComponent));
		if (!characterControllerComponent)
			return;
		
		IEntity inHand = IEntity.Cast(characterControllerComponent.GetAttachedGadgetAtLeftHandSlot());
		if (!inHand)
			return;
		
		SCR_RadioComponent radioComponent = SCR_RadioComponent.Cast(inHand.FindComponent(SCR_RadioComponent));
		if (!radioComponent)
			return;
		
		// Open up phone menu!
		
		Print("Open menu");
	}
}