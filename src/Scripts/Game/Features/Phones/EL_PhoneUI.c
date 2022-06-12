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
			
		/*
		SCR_InventoryStorageManagerComponent inventoryManager = SCR_InventoryStorageManagerComponent.Cast(m_MainEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		if (!inventoryManager)
			return;
		
		array<IEntity> outItems = new array<IEntity>();
		inventoryManager.GetItems(outItems);
		
		foreach (IEntity item : outItems)
		{
			if (item.GetPrefabData().GetPrefabname() == ""
		}
		*/
		
		SCR_CharacterControllerComponent characterControllerComponent = SCR_CharacterControllerComponent.Cast(user.FindComponent(SCR_CharacterControllerComponent));
		if (!characterControllerComponent)
			return;
		
		IEntity inHand = IEntity.Cast(characterControllerComponent.GetAttachedGadgetAtLeftHandSlot());
		if (!inHand)
			return;
		
		InventoryItemComponent inventoryItemComponent = InventoryItemComponent.Cast(inHand.FindComponent(InventoryItemComponent));
		if (!inventoryItemComponent)
			return;
		
		
		
		Print("End");
		//characterControllerComponent.TakeGadgetInLeftHand();
		
	}
}