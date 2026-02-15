#include <Geode/Geode.hpp>
#include <Geode/modify/EffectGameObject.hpp>
#include <random>

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
                    
                bool enableRandomPitch = Mod::get()->getSettingValue<bool>("enable-random-pitch");
                float randomPitch = 1.0f;

                if (enableRandomPitch) {
                    float minPitch = Mod::get()->getSettingValue<float>("min-pitch");
                    float maxPitch = Mod::get()->getSettingValue<float>("max-pitch");
                    
                    static std::random_device rd;
                    static std::mt19937 gen(rd());
                    std::uniform_real_distribution<float> dis(minPitch, maxPitch);
                    
                    randomPitch = dis(gen);
                }
                    
                    FMODAudioEngine::get()->playEffectAdvanced(
                        inbuiltSound,
                        1.0f,
                        0.0f,
                        1.0f,
                        randomPitch,
                        false,
                        false,
                        0,
                        0,
                        0,
                        0,
                        false,
                        0,
                        false,
                        false,
                        0,
                        0,
                        0.0f,
                        0
                    );
                } else {
                    float minPitch = Mod::get()->getSettingValue<float>("min-pitch");
                    float maxPitch = Mod::get()->getSettingValue<float>("max-pitch");
                    std::string soundPath = geode::utils::string::pathToString(uploadedSound);
                    bool enableRandomPitch = Mod::get()->getSettingValue<bool>("enable-random-pitch");
                    float randomPitch = 1.0f;
                    
                    if (enableRandomPitch) {
                        float minPitch = Mod::get()->getSettingValue<float>("min-pitch");
                        float maxPitch = Mod::get()->getSettingValue<float>("max-pitch");
                        
                        static std::random_device rd;
                        static std::mt19937 gen(rd());
                        std::uniform_real_distribution<float> dis(minPitch, maxPitch);
                        
                        randomPitch = dis(gen);
                    }
                    FMODAudioEngine::get()->playEffectAdvanced(
                        soundPath.c_str(),
                        1.0f,
                        0.0f,
                        1.0f,
                        randomPitch,
                        false,
                        false,
                        0,
                        0,
                        0,
                        0,
                        false,
                        0,
                        false,
                        false,
                        0,
                        0,
                        0.0f,
                        0
                    );
                }  
            } else {

                bool enableRandomPitch = Mod::get()->getSettingValue<bool>("enable-random-pitch");
                float randomPitch = 1.0f;

                if (enableRandomPitch) {
                    float minPitch = Mod::get()->getSettingValue<float>("min-pitch");
                    float maxPitch = Mod::get()->getSettingValue<float>("max-pitch");
                    
                    static std::random_device rd;
                    static std::mt19937 gen(rd());
                    std::uniform_real_distribution<float> dis(minPitch, maxPitch);
                    
                    randomPitch = dis(gen);
                }

                FMODAudioEngine::get()->playEffectAdvanced(
                    "gold01.ogg",
                    1.0f,
                    0.0f,
                    1.0f,
                    randomPitch,
                    false,
                    false,
                    0,
                    0,
                    0,
                    0,
                    false,
                    0,
                    false,
                    false,
                    0,
                    0,
                    0.0f,
                    0
                );
                return;
        
            }

        }

        EffectGameObject::triggerObject(layer, coinID, targets);
    }
};
