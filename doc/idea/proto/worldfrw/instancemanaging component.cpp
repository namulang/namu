class InstanceBlock : public Instance {
};
class MemoryMap : public ? {
};
class InstanceManager : public ? {
	Result& stamp(Instance& newone) {
		WRD_IS_NULL(newone)
		if(newone.getBlock().isExist())
			return AlreadyDone.info("");

		InstanceBlock& blk = ....getVacant()
		newone.Instance::operator=(blk);
		return Success;
	}
};
