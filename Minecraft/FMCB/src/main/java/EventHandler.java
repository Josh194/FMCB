package main.java;

import net.minecraft.init.Blocks;
import net.minecraft.item.ItemStack;
import net.minecraft.tileentity.TileEntity;
import net.minecraft.util.EnumFacing;
import net.minecraft.util.math.BlockPos;
import net.minecraft.util.text.TextComponentString;
import net.minecraftforge.fml.common.Mod;
import net.minecraftforge.fml.common.eventhandler.SubscribeEvent;
import net.minecraftforge.fml.common.gameevent.PlayerEvent.PlayerLoggedInEvent;
import net.minecraftforge.fml.common.gameevent.TickEvent;
import net.minecraftforge.fml.common.gameevent.TickEvent.Phase;
import net.minecraftforge.items.CapabilityItemHandler;
import net.minecraftforge.items.IItemHandler;

@Mod.EventBusSubscriber
public class EventHandler {

	@SubscribeEvent
	public static void onWorldLoad(PlayerLoggedInEvent event) {
		if (!event.player.world.isRemote) {
			event.player.sendMessage(new TextComponentString("FMCB server successfully loaded"));
		}
	}

	@SubscribeEvent
	public static void onTick(TickEvent.WorldTickEvent event) {
		if (event.phase == Phase.END) {
			if (event.world.getBlockState(new BlockPos(0, 67, 0)).getBlock() == Blocks.CHEST) {
				TileEntity container = event.world.getTileEntity(new BlockPos(0, 67, 0));
				IItemHandler itemHandler = container.getCapability(CapabilityItemHandler.ITEM_HANDLER_CAPABILITY,
						EnumFacing.NORTH);

				itemHandler.insertItem(0, new ItemStack(Blocks.COBBLESTONE, 1), false);
			}
		}
	}

}
