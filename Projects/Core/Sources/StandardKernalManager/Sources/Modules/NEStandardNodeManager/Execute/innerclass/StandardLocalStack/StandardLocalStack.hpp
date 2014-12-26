class NE_DLL StandardLocalStack : public NENodeManager::LocalStack
{
	//	프렌드 선언:
public:
	friend class NEStandardNodeManager;

	//	생성자:
public:
	StandardLocalStack();
	StandardLocalStack(const StandardLocalStack& source);

	//	소멸자:
public:
	virtual ~StandardLocalStack();

	//	연산자 오버로딩:
public:
	const StandardLocalStack& operator=(const StandardLocalStack& source);
	bool operator==(const StandardLocalStack& source) const;
	bool operator!=(const StandardLocalStack& source) const;

	//	접근자:
public:
	virtual NENode& getRecentNode();
	virtual const NENode& getRecentNode() const;
	virtual NEModule& getRecentModule();
	virtual const NEModule& getRecentModule() const;
	virtual NEModuleCodeSet& getRecentModuleSet();
	virtual const NEModuleCodeSet& getRecentModuleSet() const;
	virtual NENodeCodeSet& getRecentNodeSet();
	virtual const NENodeCodeSet& getRecentNodeSet() const;
	virtual type_index getRecentModuleSetIndex() const;
	virtual type_index getRecentNodeSetIndex() const;
	virtual type_result getRecentResultCode() const;
	virtual const NECode& getRecentPriorityCode() const;
	virtual type_count getFrameCount() const;
	virtual type_index getRecentNodeRealIndex() const;
	virtual type_index getRecentModuleRealIndex() const;

protected:	
	virtual void _setRecentNode(NENode& new_node);
	virtual void _setRecentModuleSet(NEModuleCodeSet& new_moduleset);
	virtual void _setRecentModuleSetIndex(type_index moduleset_index);
	virtual void _setRecentNodeSet(NENodeCodeSet& new_node_codeset);
	virtual void _setRecentNodeSetIndex(type_index nodeset_index);
	virtual void _setRecentResultCode(type_result new_result);
	virtual void _setRecentPriorityCode(const NECode& new_priority);
	virtual void _setFrameCount(type_count new_frame_count);
	virtual void _setRecentNodeRealIndex(type_index real_node_index);

	//	인터페이스:
	//		상속:
	//			NEObject:
protected:
	virtual void release();

public:
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEObject& clone() const;
	virtual type_result isValid() const;

	//	내부 함수:
public:
	const StandardLocalStack& _assign(const StandardLocalStack& source);

	//	멤버변수:
protected:
	type_count _frame_count;
	NENode* _recent_node_pointer;
	NEModuleCodeSet* _recent_moduleset_pointer;
	NENodeCodeSet* _recent_nodeset_pointer;
	type_index _recent_moduleset_index;
	type_index _recent_nodeset_index;
	type_result _recent_result;
	NECode _recent_priority;	
	type_index _recent_node_real_index;
	type_index _recent_module_real_index;
};
