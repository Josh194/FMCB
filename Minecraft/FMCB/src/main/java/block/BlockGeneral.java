package main.java.block;

import main.java.init.ModBlocks;
import net.minecraft.block.Block;
import net.minecraft.block.material.Material;
import net.minecraft.creativetab.CreativeTabs;

public class BlockGeneral extends Block {
	
	public BlockGeneral(Material material, String name) {
		super(material);

		setUnlocalizedName(name);
		setRegistryName(name);
		
		setCreativeTab(CreativeTabs.FOOD);
		
		ModBlocks.blocks.add(this);
	}


}