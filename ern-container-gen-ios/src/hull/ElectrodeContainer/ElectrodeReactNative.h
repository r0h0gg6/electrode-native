/*
 * Copyright 2017 WalmartLabs

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ElectrodePluginConfig.h"

{{#hasAtleastOneApiImplConfig}}
{{#apiImplementations}}
{{#hasConfig}}
@class {{apiName}}ApiConfig;
{{/hasConfig}}
{{/apiImplementations}}
{{/hasAtleastOneApiImplConfig}}

{{#hasApiImpl}}
@protocol APIImplsConfigWrapperDelegate <NSObject>
{{/hasApiImpl}}
{{#hasAtleastOneApiImplConfig}}
@required
{{/hasAtleastOneApiImplConfig}}
{{#apiImplementations}}
{{#hasConfig}}
- ({{apiName}}ApiConfig *_Nonnull){{apiVariableName}}ApiConfig;
{{/hasConfig}}
{{/apiImplementations}}
{{#hasApiImpl}}
@end
{{/hasApiImpl}}


NS_ASSUME_NONNULL_BEGIN

@interface ElectrodeContainerConfig: NSObject <ElectrodePluginConfig>
@property (nonatomic, assign) BOOL debugEnabled;
@property (nonatomic, copy) NSString *packagerHost;
@property (nonatomic, copy) NSString *packagerPort;
@property (nonatomic, copy) NSString *bundleStoreHostPort;
@end

@protocol MiniAppViewDelegate <NSObject>
- (void)rootViewDidChangeIntrinsicSize:(UIView *)rootView;
@end

@protocol ERNDelegate <NSObject>
- (void)reactNativeDidInitialize;
@optional
- (void)rctModuleDidInitialize;
@end

////////////////////////////////////////////////////////////////////////////////
#pragma mark - ElectrodeReactNative
/**
 Container for Electrode plugins and React Native bundles that isolates
 logic, files and set up from Native engineers.
 */
@interface ElectrodeReactNative : NSObject

/**
 To load default bundle. Always `localhost:8080`
 */
@property (nonatomic, copy) NSString *defaultHostAndPort;

/**
 Create a singleton instance of ElectrodeReactNative with the ability to set
 configurations for the plugins associated with the container.

 @return A singleton instance of ElectrodeReactNative.
 */
+ (instancetype)sharedInstance;

// Whenever you need to destroy the singleton, call this reset method.
+ (void)destroyInstance;

/**
 Start an instance of ElectrodeReactNative with the ability to set
 configurations for the plugins associated with the container. Only needed to be
 called once.

 @param reactContainerConfig NSDictionary that uses ERN keys such as ERNCodePushConfig
 to store NSDictionary of configurations. The main key signifies which plugin
 the configuration is for, the subsequent NSDictionary is the actual
 configuration. This allows the ability to pass in multiple configurations for
 multiple plugins.
 */

+ (void)startWithConfigurations:(id<ElectrodePluginConfig>)reactContainerConfig
                        {{#plugins}}
                        {{#configurable}}
                        {{{lcname}}}: (id<ElectrodePluginConfig>) {{{lcname}}}
                        {{/configurable}}
                        {{/plugins}}
                        {{#hasAtleastOneApiImplConfig}}
                        apiImplementationsConfig: (NSObject <APIImplsConfigWrapperDelegate> *) apiImplConfig
                        {{/hasAtleastOneApiImplConfig}}
                        __attribute((deprecated("use -startWithConfigurations:ernDelegate instead")));

+ (void)startWithConfigurations:(id<ElectrodePluginConfig>)reactContainerConfig ernDelegate:(id<ERNDelegate> _Nullable)ernDelegate
                        {{#plugins}}
                        {{#configurable}}
                        {{{lcname}}}: (id<ElectrodePluginConfig> _Nullable) {{{lcname}}}
                        {{/configurable}}
                        {{/plugins}}
                        {{#hasAtleastOneApiImplConfig}}
                        apiImplementationsConfig: (NSObject <APIImplsConfigWrapperDelegate> *) apiImplConfig
                        {{/hasAtleastOneApiImplConfig}};


/**
 Returns a react native miniapp (from a JSBundle) inside a view controller.

 @param name The name of the mini app, preferably the same name as the jsbundle
 without the extension.
 @param properties Any configuration to set up the mini app with.
 @return A UIViewController containing the view of the miniapp.
 */
- (UIViewController *)miniAppWithName:(NSString *)name
                           properties:(NSDictionary * _Nullable)properties
        __attribute((deprecated("use -miniAppWithName:properties:overlay:sizeFlexibility:delegate instead")));

/**
 Returns a react native miniapp (from a JSBundle) inside a view controller.

 @param name The name of the mini app, preferably the same name as the jsbundle
 without the extension.
 @param properties Any configuration to set up the mini app with.
 @param overlay determines if view should be rendered as an overlay.
 @param sizeFlexibilty defines size flexibility type of the root view
 @param delegate the object to register as the miniapp's delegate.
 @return A UIViewController containing the view of the miniapp.
 */
- (UIViewController *)miniAppWithName:(NSString *)name
                           properties:(NSDictionary *_Nullable)properties
                              overlay:(BOOL)overlay
                      sizeFlexibility:(NSInteger)sizeFlexibility
                             delegate:(id<MiniAppViewDelegate> _Nullable)delegate;

/**
 Returns a react native miniapp (from a JSBundle) inside a view.

 @param name The name of the mini app, preferably the same name as the jsbundle
 without the extension.
 @param properties Any configuration to set up the mini app with.
 @return a UIView of the miniapp.
 */
- (UIView *)miniAppViewWithName:(NSString *)name
                     properties:(NSDictionary *_Nullable)properties
        __attribute((deprecated("use -miniAppViewWithName:properties:overlay:sizeFlexibility:delegate instead")));

/**
 Returns a react native miniapp (from a JSBundle) inside a view.

@param name The name of the mini app, preferably the same name as the jsbundle
without the extension.
@param overlay determines if view should be rendered as an overlay.
@param properties Any configuration to set up the mini app with.
@return a UIView of the miniapp.
*/
- (UIView *)miniAppViewWithName:(NSString *)name
                     properties:(NSDictionary *_Nullable)properties
                        overlay:(BOOL)overlay
        __attribute((deprecated("use -miniAppViewWithName:properties:overlay:sizeFlexibility:delegate instead")));


/**
 Returns a react native miniapp (from a JSBundle) inside a view.

 @param name The name of the mini app, that is registered with the AppComponent.
 @param properties initialprops for a React Native miniapp.
 @param sizeFlexibilty defines size flexibility type of the root view
 @return a UIView of the miniapp.
 */
- (UIView *)miniAppViewWithName:(NSString *)name
                     properties:(NSDictionary *_Nullable)properties
                sizeFlexibility:(NSInteger)sizeFlexibilty
        __attribute((deprecated("use -miniAppViewWithName:properties:overlay:sizeFlexibility:delegate instead")));

/**
 Returns a react native miniapp (from a JSBundle) inside a view.

 @param name The name of the mini app, that is registered with the AppComponent.
 @param properties initialprops for a React Native miniapp.
 @param sizeFlexibilty defines size flexibility type of the root view
 @param delegate the object to register as the miniapp's delegate.
 @return a UIView of the miniapp.
 */
- (UIView *)miniAppViewWithName:(NSString *)name
                     properties:(NSDictionary *_Nullable)properties
                sizeFlexibility:(NSInteger)sizeFlexibilty
                       delegate:(id<MiniAppViewDelegate> _Nullable)delegate
        __attribute((deprecated("use -miniAppViewWithName:properties:overlay:sizeFlexibility:delegate instead")));

/**
 Returns a react native miniapp (from a JSBundle) inside a view.

 @param name The name of the mini app, that is registered with the AppComponent.
 @param properties initialprops for a React Native miniapp.
 @param overlay determines if view should be rendered as an overlay.
 @param sizeFlexibilty defines size flexibility type of the root view
 @param delegate the object to register as the miniapp's delegate.
 @return a UIView of the miniapp.
 */
- (UIView *)miniAppViewWithName:(NSString *)name
                     properties:(NSDictionary *_Nullable)properties
                        overlay:(BOOL)overlay
                sizeFlexibility:(NSInteger)sizeFlexibility
                       delegate:(id<MiniAppViewDelegate> _Nullable)delegate;

/**
 Call this to update an RCTRootView with new props. Calling this with new props will cause the view to be rerendered.
 Request will be ignored if the returned view is not an RCTRootView instance.
 */
- (void)updateView:(UIView *)view withProps:(NSDictionary *)newProps;

@end
NS_ASSUME_NONNULL_END
