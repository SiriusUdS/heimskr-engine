/**
 * @file Frame.cpp
 * @brief Implementation of the FrameBuffer class.
 */

#include "Frame.h"

namespace HeimskrEngine {
  /**
   * \brief Constructor for the FrameBuffer class.
   * \param width The width of the framebuffer.
   * \param height The height of the framebuffer.
   */
  FrameBuffer::FrameBuffer(int32_t width, int32_t height) : height(height), width(width) {
    glGenFramebuffers(1, &bufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, bufferID);

    CreateColorAttachment();
    CreateRenderBuffer();

    constexpr uint32_t attachments[1] = {
      GL_COLOR_ATTACHMENT0
    };

    glDrawBuffers(1, attachments);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      HEIMSKR_ERROR(fmt::format("Framebuffer is not complete. Error: {}", glCheckFramebufferStatus(GL_FRAMEBUFFER)));
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }


  /**
   * \brief Destructor for the FrameBuffer class.
   */
  FrameBuffer::~FrameBuffer() {
    glDeleteTextures(1, &color);
    glDeleteRenderbuffers(1, &render);
    glDeleteFramebuffers(1, &bufferID);
  }


  /**
   * \brief Calculates the aspect ratio of the framebuffer.
   * \return The aspect ratio of the framebuffer.
   */
  float FrameBuffer::Ratio() const {
    return static_cast<float>(width) / static_cast<float>(height);
  }


  /**
   * \brief Resizes the framebuffer.
   * \param width The new width of the framebuffer.
   * \param height The new height of the framebuffer.
   */
  void FrameBuffer::Resize(int32_t width, int32_t height) {
    this->width = width;
    this->height = height;

    // Rosizing the color attachment
    glBindTexture(GL_TEXTURE_2D, color);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

    // Resizing the depth attachment
    glBindRenderbuffer(GL_RENDERBUFFER, render);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
  }


  /**
   * \brief Gets the texture ID of the framebuffer.
   * \return The texture ID of the framebuffer.
   */
  uint32_t FrameBuffer::GetTexture() const {
    return color;
  }


  /**
   * \brief Begins the framebuffer rendering.
   */
  void FrameBuffer::Begin() const {
    glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
    glViewport(0, 0, width, height);
    glClearColor(0, 0, 0, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
  }


  /**
   * \brief Ends the framebuffer rendering.
   */
  void FrameBuffer::End() const {
    glDisable(GL_MULTISAMPLE);
    glDisable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }


  /**
   * \brief Creates the color attachment for the framebuffer.
   */
  void FrameBuffer::CreateColorAttachment() {
    glGenTextures(1, &color);
    glBindTexture(GL_TEXTURE_2D, color);
    // Specify the texture minification filter when a texture needs to be displayed in a smaller size than its original size using a linear interpolation algorithm.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // Specify the texture magnification filter when a texture needs to be displayed in a larger size than its original size using a linear interpolation algorithm.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Specify the texture wrap mode when the texture coordinates are outside the range of [0, 1] horizontally. The GL_CLAMP_TO_EDGE mode will clamp the texture coordinates to the edge of the texture.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // Specify the texture wrap mode when the texture coordinates are outside the range of [0, 1] vertically. The GL_CLAMP_TO_EDGE mode will clamp the texture coordinates to the edge of the texture.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0);
  }


  /**
   * \brief Creates the render buffer for the framebuffer.
   */
  void FrameBuffer::CreateRenderBuffer() {
    glGenRenderbuffers(1, &render);
    glBindRenderbuffer(GL_RENDERBUFFER, render);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render);
  }
}
