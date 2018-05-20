/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "math.h"
#include "Vec2D.h"

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( int x,int y,Color c );
	void PutRect(int x, int y, int length, int height, Color c)
	{
		for (int j = y; j < y + height; j++)
		{
			for (int i = x; i < x + length; i++)
			{
				if (i >= 0 && i < ScreenWidth)
				{
					PutPixel(i, j, c);
				}
			}
		}

	}

	void PutCircle(int x, int y, int radius, Color c)
	{
		for (int j = y - radius; j < y + radius; j++)
		{
			for (int i = x - radius; i < x + radius; i++)
			{
				if (i >= 0 && i < ScreenWidth)
				{
					if (((int)pow((i - x), 2) + (int)pow((j - y), 2)) <= (int)pow((radius), 2))
					{
						PutPixel(i, j, c);
					}
				}
			}
		}

	}

	void PutCircleSliced(int x, int y, int radius, Color c, Vec2D direction)
	{
		for (int j = y - radius; j < y + radius; j++)
		{
			for (int i = x - radius; i < x + radius; i++)
			{
				if (i >= 0 && i < ScreenWidth)
				{
					if (((int)pow((i - x), 2) + (int)pow((j - y), 2)) <= (int)pow((radius), 2))
					{
						if (direction.Equiv(DIRECTION::LEFT) && (i - x + radius >= j - y + radius || i - x + radius + j - y + radius >= radius * 2))
						{
							PutPixel(i, j, c);
						}

						if (direction.Equiv(DIRECTION::RIGHT) && (i - x + radius < j - y + radius || i - x + radius + j - y + radius < radius * 2))
						{
							PutPixel(i, j, c);
						}

						if (direction.Equiv(DIRECTION::UP) && (i - x + radius < j - y + radius || i - x + radius + j - y + radius >= radius * 2))
						{
							PutPixel(i, j, c);
						}

						if (direction.Equiv(DIRECTION::DOWN) && (i - x + radius >= j - y + radius || i - x + radius + j - y + radius < radius * 2))
						{
							PutPixel(i, j, c);
						}

					}
				}

			}
		}

	}

	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 700;
	static constexpr int ScreenHeight = 920;
};