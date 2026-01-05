#include <Geode/Geode.hpp>
#include <Geode/modify/EffectGameObject.hpp>

using namespace geode::prelude;

class $modify(CoinSoundsHook, EffectGameObject) {
    void triggerObject(GJBaseGameLayer* layer, int coinID, gd::vector<int> const* targets) {
        
        bool isCoin = (this->m_objectType == GameObjectType::UserCoin || 
                       this->m_objectType == GameObjectType::SecretCoin);
        
        int myObjectID = this->m_objectID;
        auto playLayer = PlayLayer::get();

        if (isCoin && playLayer && !playLayer->m_isEditor) {
            auto usingCustomSounds = Mod::get()->getSettingValue<bool>("custom-sounds");
            auto inbuiltSound = Mod::get()->getSettingValue<std::string>("inbuilt-sound");
            auto uploadedSound = Mod::get()->getSettingValue<std::filesystem::path>("uploaded-sound");

            if (usingCustomSounds){
                if (inbuiltSound != "") {
                    log::info("inbuilt sound");
                    FMODAudioEngine::get()->playEffect(inbuiltSound);
                } else {
                    FMODAudioEngine::get()->playEffect(uploadedSound.string().c_str());
                    log::info("uploaded sound");
                }
            } else {
                FMODAudioEngine::get()->playEffect("gold01.ogg");
                log::info("normal sound");

            }

        }

        EffectGameObject::triggerObject(layer, coinID, targets);
    }
};
