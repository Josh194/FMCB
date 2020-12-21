package main.java;

import main.java.block.BlockGeneral;
import main.java.util.NetworkUtils;
import net.minecraft.block.Block;
import net.minecraft.item.Item;
import net.minecraft.item.ItemBlock;
import net.minecraft.util.text.TextComponentString;
import net.minecraftforge.client.event.ClientChatEvent;
import net.minecraftforge.common.DimensionManager;
import net.minecraftforge.event.RegistryEvent;
import net.minecraftforge.fml.common.Mod;
import net.minecraftforge.fml.common.eventhandler.SubscribeEvent;
import net.minecraftforge.fml.common.gameevent.PlayerEvent.PlayerLoggedInEvent;
import net.minecraftforge.fml.common.gameevent.TickEvent;
import net.minecraftforge.fml.common.gameevent.TickEvent.Phase;
import net.minecraftforge.fml.common.network.FMLNetworkEvent.ClientDisconnectionFromServerEvent;
import net.minecraftforge.fml.relauncher.Side;

@Mod.EventBusSubscriber
public class EventHandler {
	
	public static NetworkUtils netHandler = null;
	
	@SubscribeEvent
    public static void registerBlocks(RegistryEvent.Register<Block> event) {
		for (Block block : BlockGeneral.blocks) {
	        event.getRegistry().register(block);
		}
    }
	
	@SubscribeEvent
	public static void registerItemBlocks(RegistryEvent.Register<Item> event) {
		for (Block block : BlockGeneral.blocks) {
	        event.getRegistry().register(new ItemBlock(block).setRegistryName(block.getRegistryName()));
		}
	}
	
	@SubscribeEvent
	public static void onMessage(ClientChatEvent event) {
		netHandler.send(event.getMessage());
	}
	
	@SubscribeEvent
	public void onClientDisconnect(ClientDisconnectionFromServerEvent event) {
		netHandler.closeConnection();
		
		netHandler = null;
	}

	@SubscribeEvent
	public static void onWorldLoad(PlayerLoggedInEvent event) {
		if (!event.player.world.isRemote) {
			event.player.sendMessage(new TextComponentString("FMCB server successfully loaded"));
			event.player.sendMessage(new TextComponentString("Save location:\n" + DimensionManager.getCurrentSaveRootDirectory().getAbsolutePath()));
		}
	}

	@SubscribeEvent
	public static void onClientTick(TickEvent.PlayerTickEvent event) {
		if (netHandler == null) {
			if (event.side == Side.CLIENT) {
				netHandler = new NetworkUtils();
				
				netHandler.createConnection();
			}
		}
	}
	
	@SubscribeEvent
	public static void onTick(TickEvent.WorldTickEvent event) {
		if (event.phase == Phase.END) {
//			if (event.world.getBlockState(new BlockPos(0, 67, 0)).getBlock() == Blocks.CHEST) {
//				TileEntity container = event.world.getTileEntity(new BlockPos(0, 67, 0));
//				IItemHandler itemHandler = container.getCapability(CapabilityItemHandler.ITEM_HANDLER_CAPABILITY, EnumFacing.NORTH);
//
//				itemHandler.insertItem(0, new ItemStack(Blocks.COBBLESTONE, 1), false);
//			}
		}
	}

}
