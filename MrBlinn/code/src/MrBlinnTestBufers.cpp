#include "MrBlinnNucleus.hpp"
#include "MrBlinnGeometry.hpp"

namespace hln = hela::nucleus;

// ----------------------------------------------------------------------------
void MrBlinn::ndcTriangleSetup() {

  GLsizei vboNdcTraingleVerticesElSize = sizeof(decltype(vboNdcTraingleVerticesData)::value_type);
  glGenVertexArrays(1, &m_helloVAO);
  glBindVertexArray(m_helloVAO);
  glGenBuffers(1, &m_helloVBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_helloVBO);
  glBufferData(
               GL_ARRAY_BUFFER,
               warp::helpers::sizeofVector(vboNdcTraingleVerticesData),
               vboNdcTraingleVerticesData.data(),
               GL_STATIC_DRAW);
  glVertexAttribPointer(
                        glGetAttribLocation(m_helloShaderProgram, "aPos"),
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        vboNdcTraingleVerticesStrideLen * vboNdcTraingleVerticesElSize,
                        warpGlVertexAttribPointerOffset(0));
  glVertexAttribPointer(
                        glGetAttribLocation(m_helloShaderProgram, "aColor"),
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        vboNdcTraingleVerticesStrideLen * vboNdcTraingleVerticesElSize,
                        warpGlVertexAttribPointerOffset(2 * vboNdcTraingleVerticesElSize)
                        );
  glEnableVertexAttribArray(glGetAttribLocation(m_helloShaderProgram, "aPos"));
  glEnableVertexAttribArray(glGetAttribLocation(m_helloShaderProgram, "aColor"));
  glBindVertexArray(UNBIND);
  glBindBuffer(GL_ARRAY_BUFFER, UNBIND);
}

// ----------------------------------------------------------------------------
void MrBlinn::ndcTriangleDraw() {
  glUseProgram(m_helloShaderProgram);
  glBindVertexArray(m_helloVAO);
  m_uTimeLoc = glGetUniformLocation(m_helloShaderProgram, "uTime");
  glUniform1f(m_uTimeLoc, m_currTime);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)vboNdcTraingleVerticesData.size() / vboNdcTraingleVerticesStrideLen);
  glBindVertexArray(UNBIND);
  glUseProgram(UNUSE);
}

// ----------------------------------------------------------------------------
void MrBlinn::testCubeSetup() {
  GLint shaderCubeTestAttrPos = glGetAttribLocation(shaderBlinn01Program, "aPos");
  GLint shaderCubeTestAttrColor = glGetAttribLocation(shaderBlinn01Program, "aColor");
  GLint shaderCubeTestAttrTexCoord = glGetAttribLocation(shaderBlinn01Program, "aTexCoord");

  glGenVertexArrays(1, &testCubeBuff.vao);
  glBindVertexArray(testCubeBuff.vao);

  glGenBuffers(1, &testCubeBuff.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, testCubeBuff.vbo);
  GLsizei strideDataTypeSize = 0;

  glBufferData(
               GL_ARRAY_BUFFER,
               warp::helpers::sizeofVector(eboTestCubeVerticesData),
               eboTestCubeVerticesData.data(),
               GL_STATIC_DRAW);
  strideDataTypeSize = sizeof(decltype(eboTestCubeVerticesData)::value_type);

  // stride size 21 (px, py, pz, nx, ny, nz, u, v, tx, ty, tz, bx, by, bz, cr, cg, cb, sr, sg, sg, s)
  glVertexAttribPointer(
                        shaderCubeTestAttrPos,   // postion
                        3,            // vec3 (x, y, z)
                        GL_FLOAT,
                        GL_FALSE,     // do not normalise
                        eboTestCubeVerticesStrideLen * strideDataTypeSize,
                        warpGlVertexAttribPointerOffset(0) // offset
                        );
  glVertexAttribPointer(
                        shaderCubeTestAttrTexCoord,   // UVs
                        2,            // vec2 (u, v)
                        GL_FLOAT,
                        GL_FALSE,
                        eboTestCubeVerticesStrideLen * strideDataTypeSize,
                        warpGlVertexAttribPointerOffset(6* strideDataTypeSize) // offset
                        );
  glVertexAttribPointer(
                        shaderCubeTestAttrColor,   // color
                        3,            // vec3 (r, g, b)
                        GL_FLOAT,
                        GL_FALSE,
                        eboTestCubeVerticesStrideLen * strideDataTypeSize,
                        warpGlVertexAttribPointerOffset(14* strideDataTypeSize)
                        );

  glEnableVertexAttribArray(shaderCubeTestAttrPos);
  glEnableVertexAttribArray(shaderCubeTestAttrColor);
  glEnableVertexAttribArray(shaderCubeTestAttrTexCoord);


  glGenBuffers(1, &testCubeBuff.vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testCubeBuff.vbo); // glBindBuffer stored in VAO
  glBufferData(
               GL_ELEMENT_ARRAY_BUFFER,
               warp::helpers::sizeofVector(eboTestCubeIndicesData),
               eboTestCubeIndicesData.data(),
               GL_STATIC_DRAW);
  glBindVertexArray(UNBIND);
  glBindBuffer(GL_ARRAY_BUFFER, UNBIND);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UNBIND);
}

// ----------------------------------------------------------------------------
void MrBlinn::testCubeDraw() {

  model = glm::mat4(1.0f);
  //model = glm::rotate(model, timerProgramHolder.curr * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
  model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

  glm::mat4 MVP = projection * view * model; // calculate once on CPU

  glActiveTexture(GL_TEXTURE0 + tex_TC002.prefUnit);
  glBindTexture(GL_TEXTURE_2D, tex_TC002.base);
  glActiveTexture(GL_TEXTURE0 + 0);

  glUseProgram(shaderBlinn01Program);
  glUniform1i(glGetUniformLocation(shaderBlinn01Program, "uTexture"), tex_TC002.prefUnit);

  // we could store uniform location variables and not query it in every draw cycle (as done for attribute locations in setup()), but whatever
  glUniformMatrix4fv(glGetUniformLocation(shaderBlinn01Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(glGetUniformLocation(shaderBlinn01Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(shaderBlinn01Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(shaderBlinn01Program, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
  glUniform1f(glGetUniformLocation(shaderBlinn01Program, "uTime"), timerProgramHolder.curr);


  glBindVertexArray(testCubeBuff.vao);
  glDrawElements(
                 GL_TRIANGLES,
                 (GLsizei)eboTestCubeIndicesData.size(),
                 eboTestCubeIndicesGlType,
                 warpGlIndicesPtr0);
  glBindVertexArray(UNBIND);
  glUseProgram(UNUSE);

}

// ----------------------------------------------------------------------------
void MrBlinn::testPlaneSetup() {

  GLint attrLocaPos = glGetAttribLocation(shaderBlinn01Program, "aPos");
  GLint attrLocaColor = glGetAttribLocation(shaderBlinn01Program, "aColor");
  GLint attrLocaTexCoord = glGetAttribLocation(shaderBlinn01Program, "aTexCoord");

  glGenVertexArrays(1, &testPlaneBuff.vao);
  glBindVertexArray(testPlaneBuff.vao);

  glGenBuffers(1, &testPlaneBuff.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, testPlaneBuff.vbo);

  glBufferData(
               GL_ARRAY_BUFFER,
               warp::helpers::sizeofVector(eboTestPlaneVerticesData),
               eboTestPlaneVerticesData.data(),
               GL_STATIC_DRAW);
  GLsizei strideDataTypeSize = sizeof(decltype(eboTestPlaneVerticesData)::value_type);
  // stride size 21 (px, py, pz, nx, ny, nz, u, v, tx, ty, tz, bx, by, bz, cr, cg, cb, sr, sg, sg, s)
  glVertexAttribPointer(
                        attrLocaPos,   // postion
                        3,            // vec3 (x, y, z)
                        GL_FLOAT,
                        GL_FALSE,
                        eboTestPlaneVerticesStrideLen * strideDataTypeSize,
                        warpGlVertexAttribPointerOffset(0* strideDataTypeSize)
                        );
  glVertexAttribPointer(
                        attrLocaTexCoord,   // UVs
                        2,            // vec2 (u, v)
                        GL_FLOAT,
                        GL_FALSE,
                        eboTestPlaneVerticesStrideLen * strideDataTypeSize,
                        warpGlVertexAttribPointerOffset(6* strideDataTypeSize)
                        );
  glVertexAttribPointer(
                        attrLocaColor,   // color
                        3,            // vec3 (r, g, b)
                        GL_FLOAT,
                        GL_FALSE,
                        eboTestPlaneVerticesStrideLen * strideDataTypeSize,
                        warpGlVertexAttribPointerOffset(14* strideDataTypeSize)
                        );

  glEnableVertexAttribArray(attrLocaPos);
  glEnableVertexAttribArray(attrLocaColor);
  glEnableVertexAttribArray(attrLocaTexCoord);

  glGenBuffers(1, &testPlaneBuff.ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testPlaneBuff.ebo);
  glBufferData(
               GL_ELEMENT_ARRAY_BUFFER,
               warp::helpers::sizeofVector(eboTestPlaneIndicesData),
               eboTestPlaneIndicesData.data(),
               GL_STATIC_DRAW);
  glBindVertexArray(UNBIND);
  glBindBuffer(GL_ARRAY_BUFFER, UNBIND);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UNBIND);
}

// ----------------------------------------------------------------------------
void MrBlinn::testPlaneDraw() {
  model = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(4.0f));

  glm::mat4 MVP = projection * view * model;

  glActiveTexture(GL_TEXTURE0 + tex_DIRT006.prefUnit);
  glBindTexture(GL_TEXTURE_2D, tex_DIRT006.base);
  glActiveTexture(GL_TEXTURE0 + 0);

  glUseProgram(shaderBlinn01Program);
  glUniform1i(glGetUniformLocation(shaderBlinn01Program, "uTexture"), tex_DIRT006.prefUnit);

  glUniformMatrix4fv(glGetUniformLocation(shaderBlinn01Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(glGetUniformLocation(shaderBlinn01Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(shaderBlinn01Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(shaderBlinn01Program, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
  glUniform1f(glGetUniformLocation(shaderBlinn01Program, "uTime"), timerProgramHolder.curr);


  glBindVertexArray(testPlaneBuff.vao);
  glDrawElements(
                 GL_TRIANGLES,
                 (GLsizei)eboTestPlaneIndicesData.size(),
                 eboTestPlaneIndicesGLType,
                 warpGlIndicesPtr0);
  glBindVertexArray(UNBIND);
  glUseProgram(UNUSE);
}
