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
                    FMODAudioEngine::get()->playEffect(inbuiltSound);
                } else {
                    std::string soundPath = geode::utils::string::pathToString(uploadedSound);
                    FMODAudioEngine::get()->playEffect(soundPath.c_str());
                }  
            } else {
                FMODAudioEngine::get()->playEffect("gold01.ogg");
            }

        }

        EffectGameObject::triggerObject(layer, coinID, targets);
    }
};
