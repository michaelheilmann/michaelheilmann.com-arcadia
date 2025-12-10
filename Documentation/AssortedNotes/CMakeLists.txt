# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
#
# Permission to use, copy, modify, and distribute this software for any
# purpose without fee is hereby granted, provided that this entire notice
# is included in all copies of any software which is or includes a copy
# or modification of this software and in all copies of the supporting
# documentation for such software.
#
# THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
# WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
# REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
# OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

cmake_minimum_required(VERSION 4.1.3)

BeginTemplateEngine(${MyProjectName}.Website.Generate.AssortedNotes "Website")

  # Build "best-practices-for-access-tokens-angular-edition.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/best-practices-for-access-tokens-angular-edition.html.te"
                   "${REPOSITORY_SOURCE_DIR}/../.build/assorted-notes/best-practices-for-access-tokens-angular-edition.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/../website.env")

  # Build "why-use-refresh-tokens-angular-edition.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/why-use-refresh-tokens-angular-edition.html.te"
                   "${REPOSITORY_SOURCE_DIR}/../.build/assorted-notes/why-use-refresh-tokens-angular-edition.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/../website.env")

  # Build "togaf-for-software-engineers-buy-in-edition.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/togaf-for-software-engineers-buy-in-edition.html.te"
                   "${REPOSITORY_SOURCE_DIR}/../.build/assorted-notes/togaf-for-software-engineers-buy-in-edition.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/../website.env")

  # Build "information-security-data-security-and-data-privacy-commonalities-similarities-and-differences.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/information-security-data-security-and-data-privacy-commonalities-similarities-and-differences.html.te"
                   "${REPOSITORY_SOURCE_DIR}/../.build/assorted-notes/information-security-data-security-and-data-privacy-commonalities-similarities-and-differences.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/../website.env")

  # Build "setting-up-a-cloud-landing-zone-aws-edition.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/setting-up-a-cloud-landing-zone-aws-edition.html.te"
                   "${REPOSITORY_SOURCE_DIR}/../.build/assorted-notes/setting-up-a-cloud-landing-zone-aws-edition.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/../website.env")

EndTemplateEngine()
