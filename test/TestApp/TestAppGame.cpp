//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include "TestAppGame.hpp"
#include <utility>
#include "SpriteRenderer.hpp"

namespace TestApp {
namespace {

static Matrix3x3 CreateViewMatrix2D(Transform2D const& transform, Camera2D const& camera)
{
	return Matrix3x3::CreateTranslation({-transform.Position.X, -transform.Position.Y})*
		Matrix3x3::CreateRotationZ(-transform.Rotation) *
		Matrix3x3::CreateScale({camera.Zoom(), camera.Zoom(), 1});
}

}// unnamed namespace
//-----------------------------------------------------------------------
TestAppGame::TestAppGame(std::shared_ptr<GameHost> const& gameHostIn)
	: gameHost(gameHostIn)
{
	POMDOG_ASSERT(gameHostIn);
	graphicsContext = gameHost->GraphicsContext();
}
//-----------------------------------------------------------------------
TestAppGame::~TestAppGame() = default;
//-----------------------------------------------------------------------
void TestAppGame::Initialize()
{
	auto window = gameHost->Window();
	window->Title("TestApp - Enjoy Game Dev, Have Fun.");
	window->AllowPlayerResizing(false);
	
	auto graphicsDevice = gameHost->GraphicsDevice();
	auto assets = gameHost->AssetManager();

	{
		auto sampler = SamplerState::CreatePointWrap(graphicsDevice);
		graphicsContext->SetSamplerState(0, sampler);

		texture = assets->Load<Texture2D>("pomdog.png");
	}
	
	spriteRenderer = std::unique_ptr<SpriteRenderer>(new SpriteRenderer(gameHost));
	
	
	{
		// NOTE: Create main camera:
		auto gameObject = gameWorld.CreateObject();;
		mainCameraID = gameObject->ID();
		
		auto transform = gameObject->AddComponent<Transform2D>();
		gameObject->AddComponent<CanvasItem>();
		auto sprite = gameObject->AddComponent<Sprite>();
		auto camera = gameObject->AddComponent<Camera2D>();
		sprite->Origin = Vector2{0.5f, 0.5f};
		sprite->Subrect = Rectangle(0, 0, 16, 28);
		transform->Scale = Vector2{2.5f, 2.5f};
	}
	
	for (int i = 0; i < 10; ++i)
	{
		auto gameObject = gameWorld.CreateObject();
		gameObject->AddComponent<CanvasItem>();
		auto transform = gameObject->AddComponent<Transform2D>();
		auto sprite = gameObject->AddComponent<Sprite>();
		
		transform->Position.X = i * 28 - 200;
		transform->Position.Y = (i % 5) * 40;
		sprite->Origin = Vector2{0.5f, 0.5f};
		sprite->Subrect = Rectangle(0, 0, 16, 28);
	}
}
//-----------------------------------------------------------------------
void TestAppGame::Update()
{
	static float value = 0.0f;
		value += 0.008f;
		if (value > 1.0f) {
			value = -1.0f;
		}

	for (auto gameObject: gameWorld.QueryComponents<CanvasItem, Transform2D>())
	{
		if (gameObject->ID() == mainCameraID) {
			continue;
		}
	
		auto transform = gameObject->Component<Transform2D>();
		transform->Position.X += 1.0f;
		if (transform->Position.X > 350.0f) {
			transform->Position.X = -140.0f;
		}
		transform->Scale.X = transform->Scale.Y = 2.0f;//(0.5f + (value * 0.5f));
		transform->Rotation = MathConstants<float>::Pi() * value;
	}
	
	auto mouse = gameHost->Mouse();
	
	if (auto transform = gameWorld.Component<Transform2D>(mainCameraID))
	{
		if (mouse->State().LeftButton == ButtonState::Pressed)
		{
			transform->Position.X -= 5.0f;
		}
		if (mouse->State().RightButton == ButtonState::Pressed)
		{
			transform->Position.X += 5.0f;
		}
		transform->Rotation += float(mouse->State().ScrollWheel) * 0.01f;
	}
	
	if (auto camera = gameWorld.Component<Camera2D>(mainCameraID))
	{
		camera->Zoom(camera->Zoom() + float(mouse->State().ScrollWheel) * 0.01f);
	}
}
//-----------------------------------------------------------------------
void TestAppGame::Draw()
{
	graphicsContext->Clear(Color::CornflowerBlue);
	
	POMDOG_ASSERT(spriteRenderer);
	
	auto camera = gameWorld.Component<Camera2D>(mainCameraID);
	auto transform = gameWorld.Component<Transform2D>(mainCameraID);
	
	Matrix3x3 viewMatrix = CreateViewMatrix2D(*transform, *camera);
	
	spriteRenderer->Begin(viewMatrix);
	
	for (auto gameObject: gameWorld.QueryComponents<CanvasItem, Transform2D, Sprite>())
	{
		auto canvasItem = gameObject->Component<CanvasItem>();
		if (!canvasItem->Visibile) {
			continue;
		}
		
		auto transform = gameObject->Component<Transform2D>();
		auto sprite = gameObject->Component<Sprite>();
		
		float layerDepth = 0.0f;

		spriteRenderer->Draw(texture, transform->Position, transform->Scale, transform->Rotation, sprite->Subrect, sprite->Origin, layerDepth);
	}
	
	spriteRenderer->End();
	
	graphicsContext->Present();
}
//-----------------------------------------------------------------------
}// namespace TestApp
