class NE_DLL Connector : public NEModule::BaseConnector
{
public:
	type_result connect(NEKeyCodeSet& keyset);

public:
	NEModuleSelector& getWindowSelector();
	const NEModuleSelector& getWindowSelector() const;
	NEBooleanKey& isLoadFromINIWhenStart();	//	isLoadFromINI는 ini에 기록되지 않는다.
	const NEBooleanKey& isLoadFromINIWhenStart() const;
	NEBooleanKey& isVerticalSynchronized();
	const NEBooleanKey& isVerticalSynchronized() const;
	NEBooleanKey& isWindowed();
	const NEBooleanKey& isWindowed() const;
	NEBooleanKey& is32BitColor();
	const NEBooleanKey& is32BitColor() const;
	NEBooleanKey& is32BitTexture();
	const NEBooleanKey& is32BitTexture() const;
	NEIntKey& getScreenWidth();
	const NEIntKey& getScreenWidth() const;
	NEIntKey& getScreenHeight();
	const NEIntKey& getScreenHeight() const;
	NEFloatKey& getScreenRatio();
	const NEFloatKey& getScreenRatio() const;
	NEIntKey& getBackBufferCount();
	const NEIntKey& getBackBufferCount() const;
	NEIntKey& getScreenRefreshRate();
	const NEIntKey& getScreenRefreshRate() const;
	NEIntKey& getSwapEffect();
	const NEIntKey& getSwapEffect() const;
	
private:
	NEModuleSelector* _window_selector;
	NEBooleanKey* _is_load_from_ini_when_start;
	NEBooleanKey* _is_vertical_synchronized;
	NEBooleanKey* _is_windowed;
	NEBooleanKey* _is_32bit_color;
	NEBooleanKey* _is_32bit_texture;
	NEIntKey* _screen_width;
	NEIntKey* _screen_height;
	NEFloatKey* _screen_ratio;
	NEIntKey* _back_buffer_count;
	NEIntKey* _screen_refresh_rate;
	NEIntKey* _swap_effect;	
};