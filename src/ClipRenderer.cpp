#include <mine/ClipRenderer.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/io.hpp> // for io-streams
#include <mine/Logger.hpp>
#include <mine/Enforce.hpp>
#include <mine/sdl/Renderer.hpp>
#include <mine/sdl/Texture.hpp>

using namespace mine;

static glm::mat3 createViewMatrixFromRect(FRect rect)
{
  glm::mat3 translate = { 1.0, 0.0,                     0.0,
                          0.0, 1.0,                     0.0,
                          -rect.m_pos.x, -rect.m_pos.y, 1.0 };

  glm::mat3 scale = { 1.0/rect.m_dimension.x,                  0.0, 0.0,
                                       0.0, 1.0/rect.m_dimension.y, 0.0,
                                       0.0,                  0.0, 1.0 };
  // view * vec3 will result: first translate, then scale
  glm::mat3 view = scale * translate;
  return view;
}

ClipRenderer::ClipRenderer(FRect startClip, sdl::Renderer & renderer)
  : m_viewMatrix(createViewMatrixFromRect(startClip))
  , m_clip(startClip)
  , m_renderer(renderer)
{
  LOG_DEBUG(m_viewMatrix);
}

void ClipRenderer::horizontalMove(double xDelta)
{
  m_clip.m_pos.x += xDelta;
  m_viewMatrix = createViewMatrixFromRect(m_clip);
}

void ClipRenderer::verticalMove(double yDelta)
{
  m_clip.m_pos.y += yDelta;
  m_viewMatrix = createViewMatrixFromRect(m_clip);
}

void ClipRenderer::copy(const sdl::Texture & texture, const FRect & to)
{
  // Translate
  glm::vec3 pos = to.m_pos;
  glm::vec3 dim = to.m_dimension;
  dim.z = 0; // non-homogen

  // converting coordinates to normalized space
  glm::vec3 normPos = m_viewMatrix * pos;
  glm::vec3 normDim = m_viewMatrix * dim;

  Pos winSize = m_renderer.getWindowSize();
  // converting coordinates to device space
  glm::mat3 deviceMatrix = { 1.0*winSize.x, 0.0,           0.0,
                             0.0,           1.0*winSize.y, 0.0,
                             0.0,                     0.0, 1.0 };

  pos = deviceMatrix * normPos;
  dim = deviceMatrix * normDim;

  Rect transformed;
  transformed.m_pos.x = round(pos.x);
  transformed.m_pos.y = round(pos.y);
  transformed.m_dimension.x = round(dim.x);
  transformed.m_dimension.y = round(dim.y);

  // Y-axis direction is inverse
  transformed.m_pos.y = winSize.y - transformed.m_pos.y;

  // Rect transformed;
  // transformed.m_pos.x = (to.m_pos.x - m_clip.m_pos.x) * winSize.x / m_clip.m_dimension.x;
  // transformed.m_pos.y = (to.m_pos.y - m_clip.m_pos.y) * winSize.y / m_clip.m_dimension.y;
  // transformed.m_dimension.x = to.m_dimension.x * winSize.x / m_clip.m_dimension.x;
  // transformed.m_dimension.y = to.m_dimension.y * winSize.y / m_clip.m_dimension.y;

  m_renderer.copyTo(texture, transformed);
}
