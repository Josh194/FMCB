package init;

import net.minecraft.client.renderer.block.model.ModelResourceLocation;
import net.minecraft.item.Item;

public class ModItems {

    public static void init() {
        Bruj = new Item().setUnlocalizedName("test_item");
    }
    public static Item Bruj;

    @SubscribeEvent
    public static void registerItems(RegistryEvent.Register<Item> event) {
        event.getRegistry().registerAll(Bruj);
    }

}