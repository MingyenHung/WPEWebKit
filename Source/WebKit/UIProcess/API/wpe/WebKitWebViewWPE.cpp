/*
 * Copyright (C) 2017 Igalia S.L.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "config.h"
#include "WebKitWebView.h"

#include "WebKitWebViewPrivate.h"

gboolean webkitWebViewAuthenticate(WebKitWebView*, WebKitAuthenticationRequest*)
{
    return FALSE;
}

gboolean webkitWebViewScriptDialog(WebKitWebView*, WebKitScriptDialog*)
{
    return FALSE;
}

gboolean webkitWebViewRunFileChooser(WebKitWebView*, WebKitFileChooserRequest*)
{
    return FALSE;
}

/**
 * webkit_web_view_new:
 * @backend: (nullable) (transfer full): a #WebKitWebViewBackend, or %NULL to use the default
 *
 * Creates a new #WebKitWebView with the default #WebKitWebContext and
 * no #WebKitUserContentManager associated with it.
 * See also webkit_web_view_new_with_context(),
 * webkit_web_view_new_with_user_content_manager(), and
 * webkit_web_view_new_with_settings().
 *
 * Returns: The newly created #WebKitWebView
 */
WebKitWebView* webkit_web_view_new(WebKitWebViewBackend* backend)
{
    return WEBKIT_WEB_VIEW(g_object_new(WEBKIT_TYPE_WEB_VIEW,
        "backend", backend,
        "web-context", webkit_web_context_get_default(),
        nullptr));
}

/**
 * webkit_web_view_new_with_context:
 * @backend: (nullable) (transfer full): a #WebKitWebViewBackend, or %NULL to use the default
 * @context: the #WebKitWebContext to be used by the #WebKitWebView
 *
 * Creates a new #WebKitWebView with the given #WebKitWebContext and
 * no #WebKitUserContentManager associated with it.
 * See also webkit_web_view_new_with_user_content_manager() and
 * webkit_web_view_new_with_settings().
 *
 * Returns: The newly created #WebKitWebView
 */
WebKitWebView* webkit_web_view_new_with_context(WebKitWebViewBackend* backend, WebKitWebContext* context)
{
    g_return_val_if_fail(WEBKIT_IS_WEB_CONTEXT(context), nullptr);

    return WEBKIT_WEB_VIEW(g_object_new(WEBKIT_TYPE_WEB_VIEW,
        "backend", backend,
        "is-ephemeral", webkit_web_context_is_ephemeral(context),
        "web-context", context,
        nullptr));
}

/**
 * webkit_web_view_new_with_related_view: (constructor)
 * @backend: (nullable) (transfer full): a #WebKitWebViewBackend, or %NULL to use the default
 * @web_view: the related #WebKitWebView
 *
 * Creates a new #WebKitWebView sharing the same web process with @web_view.
 * This method doesn't have any effect when %WEBKIT_PROCESS_MODEL_SHARED_SECONDARY_PROCESS
 * process model is used, because a single web process is shared for all the web views in the
 * same #WebKitWebContext. When using %WEBKIT_PROCESS_MODEL_MULTIPLE_SECONDARY_PROCESSES process model,
 * this method should always be used when creating the #WebKitWebView in the #WebKitWebView::create signal.
 * You can also use this method to implement other process models based on %WEBKIT_PROCESS_MODEL_MULTIPLE_SECONDARY_PROCESSES,
 * like for example, sharing the same web process for all the views in the same security domain.
 *
 * The newly created #WebKitWebView will also have the same #WebKitUserContentManager
 * and #WebKitSettings as @web_view.
 *
 * Returns: (transfer full): The newly created #WebKitWebView
 *
 * Since: 2.4
 */
WebKitWebView* webkit_web_view_new_with_related_view(WebKitWebViewBackend* backend, WebKitWebView* webView)
{
    g_return_val_if_fail(WEBKIT_IS_WEB_VIEW(webView), nullptr);

    return WEBKIT_WEB_VIEW(g_object_new(WEBKIT_TYPE_WEB_VIEW,
        "backend", backend,
        "user-content-manager", webkit_web_view_get_user_content_manager(webView),
        "settings", webkit_web_view_get_settings(webView),
        "related-view", webView,
        nullptr));
}

/**
 * webkit_web_view_new_with_settings:
 * @backend: (nullable) (transfer full): a #WebKitWebViewBackend, or %NULL to use the default
 * @settings: a #WebKitSettings
 *
 * Creates a new #WebKitWebView with the given #WebKitSettings.
 * See also webkit_web_view_new_with_context(), and
 * webkit_web_view_new_with_user_content_manager().
 *
 * Returns: The newly created #WebKitWebView
 *
 * Since: 2.6
 */
WebKitWebView* webkit_web_view_new_with_settings(WebKitWebViewBackend* backend, WebKitSettings* settings)
{
    g_return_val_if_fail(WEBKIT_IS_SETTINGS(settings), nullptr);

    return WEBKIT_WEB_VIEW(g_object_new(WEBKIT_TYPE_WEB_VIEW,
        "backend", backend,
        "settings", settings,
        nullptr));
}

/**
 * webkit_web_view_new_with_user_content_manager:
 * @backend: (nullable) (transfer full): a #WebKitWebViewBackend, or %NULL to use the default
 * @user_content_manager: a #WebKitUserContentManager.
 *
 * Creates a new #WebKitWebView with the given #WebKitUserContentManager.
 * The content loaded in the view may be affected by the content injected
 * in the view by the user content manager.
 *
 * Returns: The newly created #WebKitWebView
 *
 * Since: 2.6
 */
WebKitWebView* webkit_web_view_new_with_user_content_manager(WebKitWebViewBackend* backend, WebKitUserContentManager* userContentManager)
{
    g_return_val_if_fail(WEBKIT_IS_USER_CONTENT_MANAGER(userContentManager), nullptr);

    return WEBKIT_WEB_VIEW(g_object_new(WEBKIT_TYPE_WEB_VIEW,
        "backend", backend,
        "user-content-manager", userContentManager,
        nullptr));
}
