package main.java;

import net.minecraft.util.text.TextComponentString;
import net.minecraftforge.fml.common.Mod;
import net.minecraftforge.fml.common.eventhandler.SubscribeEvent;
import net.minecraftforge.fml.common.gameevent.PlayerEvent.PlayerLoggedInEvent;

@Mod.EventBusSubscriber
public class EventHandler {
	
	@SubscribeEvent
    public static void onWorldLoad(PlayerLoggedInEvent event) {
		//if (event.getWorld().isRemote) {
			event.player.sendMessage(new TextComponentString("FMCB client successfully loaded"));
		//} else {
			//Minecraft.getMinecraft().player.sendChatMessage("FMCB server successfully loaded");
		//}

	}
	
}
