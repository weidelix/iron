#pragma once
#include "Layer.h"

namespace Iron
{
    class Viewport : public Layer
    {
    private: 

    public:
        void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
    };
}