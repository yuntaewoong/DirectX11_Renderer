#include "Light/PointLight.h"

#include "Renderer/DataTypes.h"

namespace library
{
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   PointLight::PointLight

      Summary:  Constructor

      Args:     const XMFLOAT4& position
                  Position of the light
                const XMFLOAT4& color
                  Position of the color
                FLOAT attenuationDistance
                  Attenuation distance

      Modifies: [m_position, m_color, m_attenuationDistance].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    PointLight::PointLight(_In_ const XMFLOAT4& position, _In_ const XMFLOAT4& color, _In_ FLOAT attenuationDistance) :
        m_color(color),
        m_position(position),
        m_attenuationDistance(attenuationDistance)
    {}

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   PointLight::GetPosition

      Summary:  Returns the position of the light

      Returns:  const XMFLOAT4&
                  Position of the light
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    const XMFLOAT4& PointLight::GetPosition() const
    {
        return m_position;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   PointLight::GetColor

      Summary:  Returns the color of the light

      Returns:  const XMFLOAT4&
                  Color of the light
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    const XMFLOAT4& PointLight::GetColor() const
    {
        return m_color;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   PointLight::GetAttenuationDistance

      Summary:  Returns the attenuation distance

      Returns:  FLOAT
                  Attenuation distance
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    FLOAT PointLight::GetAttenuationDistance() const
    {
        return m_attenuationDistance;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   PointLight::Update

      Summary:  Updates the light every frame

      Args:     FLOAT deltaTime
                  Elapsed time
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    void PointLight::Update(_In_ FLOAT deltaTime)
    {
        UNREFERENCED_PARAMETER(deltaTime);
    }
}