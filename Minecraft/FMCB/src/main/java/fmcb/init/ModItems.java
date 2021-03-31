package fmcb.init;

import java.util.ArrayList;

import fmcb.item.ItemGeneral;
import net.minecraft.client.renderer.block.model.ModelResourceLocation;
import net.minecraft.item.Item;
import net.minecraftforge.client.event.ModelRegistryEvent;
import net.minecraftforge.client.model.ModelLoader;
import net.minecraftforge.event.RegistryEvent;
import net.minecraftforge.fml.common.Mod;
import net.minecraftforge.fml.common.eventhandler.SubscribeEvent;

@Mod.EventBusSubscriber(modid="fmcb")
public class ModItems {

	public static ArrayList<Item> items = new ArrayList<Item>();

    public static void init() {
        new ItemGeneral("bruj");
    }

    @SubscribeEvent
    public static void registerItems(RegistryEvent.Register<Item> event) {
    	for (Item item : items) {
            event.getRegistry().register(item);
    	}
    }

    @SubscribeEvent
    public static void registerRenders(ModelRegistryEvent event) {
    	for (Item item : items) {
            registerRender(item);
    	}
    }

    public static void registerRender(Item item){
        ModelLoader.setCustomModelResourceLocation(item, 0, new ModelResourceLocation(item.getRegistryName(), "inventory"));
    }

}