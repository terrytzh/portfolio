//
//  HUD.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/10.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef HUD_hpp
#define HUD_hpp

#include <stdio.h>
#include <sstream>
#include <vector>
#include "SDL/SDL_ttf.h"
#include "UIComponent.h"

class HUD : public UIComponent{
public:
    HUD(class Actor* owner);
    ~HUD();
    void Draw(class Shader* shader) override;
    void Update(float deltaTime) override;
    
    struct Blip{
        Vector2 mPos;
        float mAngle;
    };
    
protected:
    class Font* mFont;
    class Texture* mTimerText;
    class Texture* mCoinCountText;
    class Texture* mCheckpointText;
    class Texture* mRadar;
    class Texture* mRadarArrow;
    class Texture* mBlip;
    std::vector<Blip> mBlips;
    
    float checkpointTimer = 0.0f;
    const Vector2 RADAR_POSITION = Vector2(400.0f, -275.0f);
    const float RADAR_RANGE = 1500.0f;
    const float RADAR_RADIUS = 92.0f;
};

#endif /* HUD_hpp */
