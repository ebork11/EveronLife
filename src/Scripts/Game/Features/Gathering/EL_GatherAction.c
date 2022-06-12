class EL_GatherAction : ScriptedUserAction
{
	[Attribute("", UIWidgets.EditBox, desc: "Display name of what is being gathered")]
	private string m_GatherItemDisplayName;
	
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "Prefab what item is gathered")]
	private ResourceName m_GatherItemPrefab;

	[Attribute(defvalue:"1", UIWidgets.EditBox, desc: "Amount of items to receive")]
	private int m_AmountGathered;
	
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "Item(s) required for gathering")]
	private ResourceName m_RequiredItemPrefab;
	
	[Attribute("", UIWidgets.CheckBox, desc: "Check entire inventory too")]
	private bool m_CheckInventory;
		
	[Attribute(defvalue:"0", UIWidgets.EditBox, desc: "Amount of delay after performing action")]
	private int m_DelayTimeMilliseconds;
	
	private SCR_InventoryStorageManagerComponent m_InventoryManager;
	private bool m_CanBePerformed = true;
	private float m_EndOfDelay;
	
	//------------------------------------------------------------------------------------------------
	// User has performed the action
	// play a pickup sound and then add the correct amount to the users inventory
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		// Play sound
		auto replication = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
		
		//Todo: Replace SCR_InventoryStorageManagerComponent RPL setup with own function or better synced sound alternative
		auto inventoryManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		inventoryManager.PlayItemSound(replication.Id(), "SOUND_PICK_UP");
		
		//Spawn item
		inventoryManager.TrySpawnPrefabToStorage(m_GatherItemPrefab);
		
		//Show hint what to do with the gathered item
		EL_GameModeRoleplay.GetInstance().ShowInitalTraderHint();
		if (m_DelayTimeMilliseconds > 0) // If item has a delay between uses
		{
			m_CanBePerformed = false;
			GetGame().GetCallqueue().CallLater(ToggleCanBePerformed, m_DelayTimeMilliseconds);	
			m_EndOfDelay = GetGame().GetWorld().GetWorldTime() + m_DelayTimeMilliseconds;
		}
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("Gather %1", m_GatherItemDisplayName);
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		if (!m_CanBePerformed)
		{
			float timeLeft = (m_EndOfDelay - GetGame().GetWorld().GetWorldTime()) / 1000;
			SetCannotPerformReason(string.Format("Please wait %1 seconds", Math.Round(timeLeft)));
			return false;
		}
			
		
		m_InventoryManager = SCR_InventoryStorageManagerComponent.Cast(user.FindComponent(SCR_InventoryStorageManagerComponent));
		
		if (!m_RequiredItemPrefab) // If not required we dont need to check anything
			return true;
		
		if (m_CheckInventory) // Just check the inventory
		{
			SetCannotPerformReason("Requires item");
			
			array<IEntity> outItems = new array<IEntity>();
			m_InventoryManager.GetItems(outItems);
			
			foreach (IEntity item : outItems)
			{
				if (item.GetPrefabData().GetPrefabName() == m_RequiredItemPrefab)
					return true;
			}
		}
		else // Check hands 
		{
			SetCannotPerformReason("Requires item in hands");
			
			SCR_CharacterControllerComponent characterControllerComponent = SCR_CharacterControllerComponent.Cast(user.FindComponent(SCR_CharacterControllerComponent));
			if (!characterControllerComponent)
				return false;
			
			IEntity rightHandItem = IEntity.Cast(characterControllerComponent.GetRightHandItem());
			if (rightHandItem && rightHandItem.GetPrefabData().GetPrefabName() == m_RequiredItemPrefab)
				return true;
			
			IEntity leftHandItem = IEntity.Cast(characterControllerComponent.GetAttachedGadgetAtLeftHandSlot());
			if (leftHandItem && leftHandItem.GetPrefabData().GetPrefabName() == m_RequiredItemPrefab)
				return true;
		}
		
		return false;
 	}
}
