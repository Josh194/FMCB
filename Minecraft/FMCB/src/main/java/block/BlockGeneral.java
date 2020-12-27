package main.java.block;

import java.util.ArrayList;

import net.minecraft.block.Block;
import net.minecraft.block.material.Material;
import net.minecraft.creativetab.CreativeTabs;

public class BlockGeneral extends Block {
	
	public static ArrayList<BlockGeneral> blocks = new ArrayList<BlockGeneral>();
	
	public BlockGeneral(Material material, String name) {
		super(material);

		setUnlocalizedName(name);
		setRegistryName(name);
		
		setCreativeTab(CreativeTabs.FOOD);
		
		blocks.add(this);
	}


}