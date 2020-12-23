package items;

import net.minecraft.creativetab.CreativeTabs;
import net.minecraft.item.Item;

public class ItemBruj extends Item {

    public ItemBruj (String name){
        setUnlocalizedName(name);
        setRegistryName(name);
        setCreativeTab(CreativeTabs.FOOD);
    }

}
