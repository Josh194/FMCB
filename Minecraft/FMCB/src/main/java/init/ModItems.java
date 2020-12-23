package init;

import items.ItemBruj;
import net.minecraft.client.renderer.block.model.ModelResourceLocation;
import net.minecraft.item.Item;
import net.minecraftforge.client.event.ModelRegistryEvent;
import net.minecraftforge.client.model.ModelLoader;
import net.minecraftforge.event.RegistryEvent;
import net.minecraftforge.fml.common.Mod;
import net.minecraftforge.fml.common.eventhandler.SubscribeEvent;

@Mod.EventBusSubscriber(modid="fmcb")

public class ModItems {

    static Item Bruj;

    public static void init() {
        Bruj = new ItemBruj("bruj");
    }

    @SubscribeEvent
    public static void registerItems(RegistryEvent.Register<Item> event) {
        event.getRegistry().registerAll(Bruj);
    }

    @SubscribeEvent
    public static void registerRenders(ModelRegistryEvent event){
        registerRender(Bruj);
    }

    public static void registerRender(Item item){
        ModelLoader.setCustomModelResourceLocation(item, 0, new ModelResourceLocation( item.getRegistryName(), "inventory"));
    }

}