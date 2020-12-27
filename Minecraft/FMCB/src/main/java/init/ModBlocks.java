package main.java.init;

import net.minecraft.block.Block;
import net.minecraft.block.material.Material;
import net.minecraft.client.renderer.block.model.ModelResourceLocation;
import net.minecraft.item.Item;
import net.minecraft.item.ItemBlock;
import net.minecraftforge.client.event.ModelRegistryEvent;
import net.minecraftforge.client.model.ModelLoader;
import net.minecraftforge.event.RegistryEvent;
import net.minecraftforge.fml.common.Mod;
import net.minecraftforge.fml.common.eventhandler.SubscribeEvent;

import java.util.ArrayList;

import main.java.block.BlockGeneral;

@Mod.EventBusSubscriber(modid="fmcb")
public class ModBlocks {
	
	public static ArrayList<Block> blocks = new ArrayList<Block>();

    public static void init() {
    	new BlockGeneral(Material.ROCK, "bruh");
    }

    @SubscribeEvent
    public static void registerBlocks(RegistryEvent.Register<Block> event) {   
    	for (Block block : blocks) {
        	event.getRegistry().register(block);
        }
    }

    @SubscribeEvent
    public static void registerItemBlocks(RegistryEvent.Register<Item> event) {
    	for (Block block : blocks) {
        	event.getRegistry().register(new ItemBlock(block).setRegistryName(block.getRegistryName()));
    	}
    }

    @SubscribeEvent
    public static void registerRenders(ModelRegistryEvent event) {
    	for (Block block : blocks) {
    		registerRender(Item.getItemFromBlock(block));
    	}
    }

    public static void registerRender(Item item) {
    	ModelLoader.setCustomModelResourceLocation(item, 0, new ModelResourceLocation(item.getRegistryName(), "inventory"));
    }

}
