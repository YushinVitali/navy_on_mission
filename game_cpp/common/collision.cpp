#include "collision.hpp"

#include <memory>

#include "../../framework/draw_debug.hpp"

#include "target_point.hpp"

#include "../aircraft.hpp"
#include "../vector2.hpp"


bool CollisionAircraftAndTarget( Aircraft const& aircraft, TargetPoint const& target )
{
	const float offCenter{ 0.05f };
	const auto nosePosition{ aircraft.getPosition() + offCenter * aircraft.getForwardVector() };

	const auto direction{ target.center - nosePosition };

#ifdef DRAW_DEBUG
	drawDebug::DrawDebug::Instance()->addShape(
		std::make_unique<drawDebug::Circle>( nosePosition, 0.025f, 16, 4.0f, drawDebug::BLUE ));
	drawDebug::DrawDebug::Instance()->addShape(
		std::make_unique<drawDebug::Circle>( target.center, target.radius ) );
#endif // defined(DRAW_DEBUG)

	return direction.length() <= target.radius;
}