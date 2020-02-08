package main.java.block;

import java.util.ArrayList;

import net.minecraft.block.Block;
import net.minecraft.block.material.Material;

public class BlockGeneral extends Block {
	
	public static ArrayList<BlockGeneral> blocks = new ArrayList<BlockGeneral>();

	public BlockGeneral(Material materialIn) {
		super(materialIn);
		
		blocks.add(this);
	}

}
