package main.java;

import net.minecraft.block.Block;
import net.minecraftforge.fml.common.Mod;
import net.minecraftforge.fml.common.Mod.EventHandler;
import net.minecraftforge.fml.common.event.FMLInitializationEvent;
import net.minecraftforge.fml.common.event.FMLPreInitializationEvent;

@Mod(modid = "fmcb", useMetadata = true)
public class FMCB {

	@EventHandler
	public void preInit(FMLPreInitializationEvent event) {
		Block.registerBlocks();
	}

	@EventHandler
	public void init(FMLInitializationEvent event) {
		
	}
	
}
